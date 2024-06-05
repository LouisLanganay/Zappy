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
    const zappy_server_t *server)
{
    protocol_connection_t *connection;

    while (!TAILQ_EMPTY(&server->socket->new_connections)) {
        connection = TAILQ_FIRST(&server->socket->new_connections);
        TAILQ_REMOVE(&server->socket->new_connections, connection, entries);
        printf("New connection from %d\n", connection->fd);
        protocol_server_send_message(server->socket, connection->fd,
            "WELCOME\n");
        free(connection);
    }
    while (!TAILQ_EMPTY(&server->socket->lost_connections)) {
        connection = TAILQ_FIRST(&server->socket->lost_connections);
        TAILQ_REMOVE(&server->socket->lost_connections, connection, entries);
        printf("Lost connection from %d\n", connection->fd);
        free(connection);
    }
}

static void handle_gui_event(
    const zappy_server_t *server,
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
    printf("New GUI connected\n");
    mct(server, interlocutor, NULL);
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
    printf("New AI connected\n");
    protocol_server_send_message(server->socket, interlocutor,
        "%i\n", server->clients_nb);
    protocol_server_send_message(server->socket, interlocutor,
        " %i %i\n", server->width, server->height);
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
            ai_cmds[i].func(server, interlocutor, message + cmd_lenght + 1);
            return;
        }
    }
    suc(server, interlocutor);
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
    const protocol_payload_t *payload,
    const char *message)
{
    switch (get_connection_by_fd(server, payload->fd)) {
        case CONNECTION_AI:
            handle_ai_event(server, payload->fd, message);
        break;
        case CONNECTION_GUI:
            handle_gui_event(server, payload->fd, message);
        break;
        case CONNECTION_UNKNOWN:
            if (!strcmp(message, "GRAPHIC\n"))
                add_graphic(server, payload->fd);
            else
                add_client(server, payload->fd, message);
        break;
        default:
            break;
    }
}

bool handle_payload(
    zappy_server_t *server)
{
    protocol_payload_t *payload;
    char *message;

    handle_connection(server);
    while (!TAILQ_EMPTY(&server->socket->payloads)) {
        payload = TAILQ_FIRST(&server->socket->payloads);
        TAILQ_REMOVE(&server->socket->payloads, payload, entries);
        printf("Received message from %d\n", payload->fd);
        message = protocol_receive_message(payload);
        if (!message)
            return false;
        handle_event(server, payload, message);
        free(message);
        free(payload);
    }
    return true;
}
