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

static void handle_new_connection(
    const zappy_server_t *server)
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

static void handle_event(
    zappy_server_t *server,
    const protocol_payload_t *payload)
{
    switch (get_connection_by_fd(server, payload->fd)) {
        case CONNECTION_AI:
            verbose(server, "AI %d: %s\n", payload->fd, payload->message);
            handle_event_ai(server, payload);
            break;
        case CONNECTION_GUI:
            verbose(server, "GUI %d: %s\n", payload->fd, payload->message);
            handle_event_gui(server, payload);
            break;
        case CONNECTION_UNKNOWN:
            if (!strcmp(payload->message, "GRAPHIC"))
                create_gui(server, payload);
            else
                create_ai(server, payload);
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
