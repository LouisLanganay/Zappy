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

static void handle_connection(
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
    while (!TAILQ_EMPTY(&server->socket->lost_connections)) {
        connection = TAILQ_FIRST(&server->socket->lost_connections);
        TAILQ_REMOVE(&server->socket->lost_connections, connection, entries);
        verbose(server, "Lost connection from %d\n", connection->fd);

        ai_t *ai_t;
        TAILQ_FOREACH(ai_t, &server->ais, entries)
            if (ai_t->fd == connection->fd)
                TAILQ_REMOVE(&server->ais, ai_t, entries);
        free(connection);
    }
}

static void handle_gui_event(
    zappy_server_t *server,
    const int interlocutor,
    const char *message)
{
    uint8_t cmd_lenght;

    for (uint8_t i = 0; gui_cmds[i].func; ++i) {
        cmd_lenght = strlen(gui_cmds[i].cmd);
        if (!strncmp(message, gui_cmds[i].cmd, cmd_lenght)) {
            gui_cmds[i].func(server, interlocutor, message + cmd_lenght + 1);
            return;
        }
    }
    suc(server, interlocutor);
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
    msz(server, interlocutor, NULL);
    sgt(server, interlocutor, NULL);
    mct(server, interlocutor, NULL);
    tna(server, interlocutor, NULL);
}

static void add_client(
    zappy_server_t *server,
    const int interlocutor,
    const char *message)
{
    team_t *team = calloc(1, sizeof(team_t));
    ai_t *ai = calloc(1, sizeof(ai_t));

    if (!team || !ai)
        return;
    team->id = TAILQ_EMPTY(&server->teams) ? 1
        : TAILQ_LAST(&server->teams, teamhead)->id + 1;
    strncpy(team->name, message, 64);
    TAILQ_INSERT_TAIL(&server->teams, team, entries);
    ai->fd = interlocutor;
    ai->team = team;
    TAILQ_INSERT_TAIL(&server->ais, ai, entries);
    verbose(server, "New AI connected\n");
    protocol_server_send(server->socket, interlocutor,
        "%i", server->clients_nb);
    protocol_server_send(server->socket, interlocutor,
        " %i %i", server->width, server->height);
}

static void handle_ai_event(
    const zappy_server_t *server,
    const int interlocutor,
    const char *message)
{
    uint8_t cmd_lenght;

    for (uint8_t i = 0; ai_cmds[i].func; ++i) {
        cmd_lenght = strlen(ai_cmds[i].cmd);
        if (!strncmp(message, ai_cmds[i].cmd, cmd_lenght)) {
            ai_cmds[i].func(server, get_ai_by_id(server, interlocutor),
                message + cmd_lenght + 1);
            return;
        }
    }
    protocol_server_send(server->socket, interlocutor, "ko");
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
            handle_ai_event(server, payload->fd, payload->message);
            break;
        case CONNECTION_GUI:
            verbose(server, "GUI %d: %s\n", payload->fd, payload->message);
            handle_gui_event(server, payload->fd, payload->message);
            break;
        case CONNECTION_UNKNOWN:
            if (!strcmp(payload->message, "GRAPHIC"))
                add_graphic(server, payload->fd);
            else
                add_client(server, payload->fd, payload->message);
            break;
        default:
            break;
    }
}

bool handle_payload(
    zappy_server_t *server)
{
    protocol_payload_t *payload;

    handle_connection(server);
    while (!TAILQ_EMPTY(&server->socket->payloads)) {
        payload = TAILQ_FIRST(&server->socket->payloads);
        TAILQ_REMOVE(&server->socket->payloads, payload, entries);
        handle_event(server, payload);
        free(payload);
    }
    return true;
}
