/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** payload
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "server/ai_header.h"
#include "server/gui.h"
#include "server.h"

static void handle_new_connection(
    zappy_server_t *server)
{
    protocol_connection_t *connection;

    while (!TAILQ_EMPTY(&server->socket->new_connections)) {
        connection = TAILQ_FIRST(&server->socket->new_connections);
        TAILQ_REMOVE(&server->socket->new_connections, connection, entries);
        verbose(server, "New connection from %d\n", connection->fd);
        protocol_server_send(server->socket, connection->fd,
            "WELCOME");
        free(connection);
    }
}

static void handle_lost_connection(
    zappy_server_t *server)
{
    protocol_connection_t *connection;
    ai_t *ai;

    while (!TAILQ_EMPTY(&server->socket->lost_connections)) {
        connection = TAILQ_FIRST(&server->socket->lost_connections);
        TAILQ_REMOVE(&server->socket->lost_connections, connection, entries);
        verbose(server, "Lost connection from %d\n", connection->fd);
        ai = ai_get_by_fd(server, connection->fd);
        if (ai) {
            verbose(server, "AI disconnected\n");
            TAILQ_REMOVE(&server->ais, ai, entries);
            free(ai);
        }
        free(connection);
    }
}

static ai_t *init_ai(
    const zappy_server_t *server,
    const protocol_payload_t *payload)
{
    ai_t *ai = calloc(1, sizeof(ai_t));
    team_t *team;

    if (!ai)
        return NULL;
    *ai = (ai_t){
        .fd = payload->fd, .level = 1, .orientation = NORTH,
        .is_incantate = false, .life_span = 0, .inventory = { .food = 10 }
    };
    TAILQ_INIT(&ai->commands);
    TAILQ_INIT(&ai->incantations);
    TAILQ_FOREACH(team, &server->teams, entries)
        if (!strcmp(team->name, payload->message))
            ai->team = team;
    if (!ai->team) {
        free(ai);
        printf("\033[31m[ERROR]\033[0m Team not found\n");
        return NULL;
    }
    return ai;
}

static void add_ai(
    zappy_server_t *server,
    const protocol_payload_t *payload)
{
    ai_t *ai = init_ai(server, payload);

    if (!ai)
        return;
    TAILQ_INSERT_TAIL(&server->ais, ai, entries);
    verbose(server, "New AI connected\n");
    protocol_server_send(server->socket, payload->fd,
        "%i", server->clients_nb);
    protocol_server_send(server->socket, payload->fd,
        "%i %i", server->width, server->height);
}

static void add_graphic(
    zappy_server_t *server,
    const int interlocutor)
{
    gui_t *gui = calloc(1, sizeof(gui_t));

    if (!gui)
        return;
    gui->fd = interlocutor;
    TAILQ_INSERT_TAIL(&server->guis, gui, entries);
    verbose(server, "New GUI connected\n");
    msz(server, interlocutor, "");
    sgt(server, interlocutor, "");
    mct(server, interlocutor, "");
    tna(server, interlocutor, "");
}

static void handle_ai_event(
    zappy_server_t *server,
    const protocol_payload_t *payload)
{
    uint8_t len;
    ai_cmd_t *cmd;
    ai_t *ai = ai_get_by_fd(server, payload->fd);

    for (uint8_t i = 0; ai_cmds[i].func; ++i) {
        len = strlen(ai_cmds[i].cmd);
        if (strncmp(payload->message, ai_cmds[i].cmd, len))
            continue;
        if (ai_cmds[i].time == 0) {
            ai_cmds[i].func(server, ai, payload->message + len + 1);
            return;
        }
        cmd = calloc(1, sizeof(ai_cmd_t));
        if (!cmd)
            return;
        *cmd = (ai_cmd_t){ .func = ai_cmds[i].func, .time = ai_cmds[i].time };
        memcpy(cmd->cmd, payload->message + len, strlen(payload->message + len));
        TAILQ_INSERT_TAIL(&ai->commands, cmd, entries);
        return;
    }
    protocol_server_send(server->socket, payload->fd, "ko");
}

static void handle_gui_event(
    zappy_server_t *server,
    const protocol_payload_t *payload)
{
    uint8_t len;

    for (uint8_t i = 0; gui_cmds[i].func; ++i) {
        len = strlen(gui_cmds[i].cmd);
        if (!strncmp(payload->message, gui_cmds[i].cmd, len)) {
            gui_cmds[i].func(server, payload->fd, payload->message + len + 1);
            return;
        }
    }
    suc(server, payload->fd);
}

static connection_t get_connection_by_fd(
    const zappy_server_t *server,
    const int fd)
{
    ai_t *ai;
    gui_t *gui;

    TAILQ_FOREACH(ai, &server->ais, entries)
        if (ai->fd == fd)
            return CONNECTION_AI;
    TAILQ_FOREACH(gui, &server->guis, entries)
        if (gui->fd == fd)
            return CONNECTION_GUI;
    return CONNECTION_UNKNOWN;
}

static void handle_event(
    zappy_server_t *server,
    const protocol_payload_t *payload)
{
    switch (get_connection_by_fd(server, payload->fd)) {
        case CONNECTION_AI:
            verbose(server, "AI %d: %s\n", payload->fd, payload->message);
            handle_ai_event(server, payload);
            break;
        case CONNECTION_GUI:
            verbose(server, "GUI %d: %s\n", payload->fd, payload->message);
            handle_gui_event(server, payload);
            break;
        case CONNECTION_UNKNOWN:
            if (!strcmp(payload->message, "GRAPHIC"))
                add_graphic(server, payload->fd);
            else
                add_ai(server, payload);
            break;
    }
}

bool handle_payload(
    zappy_server_t *server)
{
    protocol_payload_t *payload;

    handle_new_connection(server);
    handle_lost_connection(server);
    while (!TAILQ_EMPTY(&server->socket->payloads)) {
        payload = TAILQ_FIRST(&server->socket->payloads);
        TAILQ_REMOVE(&server->socket->payloads, payload, entries);
        handle_event(server, payload);
        free(payload);
    }
    return true;
}
