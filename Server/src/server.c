/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** server
*/

#include <stdlib.h>
#include <stdio.h>

#include "server/gui.h"
#include "server.h"

#include <string.h>

void server_init(
    zappy_server_t *server)
{
    *server = (zappy_server_t){ .port = 4242, .width = 10, .height = 10 };
    TAILQ_INIT(&server->ais);
    TAILQ_INIT(&server->teams);
    TAILQ_INIT(&server->guis);
}

static bool display_server(
    const zappy_server_t *server)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    if (printf(
        "===================Zappy Server==================="
        "\nport = %hu\nwidth = %hu\nheight = %hu\nclients_nb = %hu\nfreq = %hu"
        "\nTeams [%hu]:",
        server->port, server->width, server->height, server->clients_nb,
        server->freq, TAILQ_EMPTY(&server->teams) ? 0
        : TAILQ_LAST(&server->teams, teamhead)->id) < 0)
        return false;
    for (team_t *team = server->teams.tqh_first; team;
        team = team->entries.tqe_next)
        if (printf("\n\t%d: %s", team->id, team->name) < 0)
            return false;
    if (printf("\nverbose = %s"
        "\n==================================================\n",
        server->verbose ? "true" : "false") < 0)
        return false;
    fflush(stdout);
    setvbuf(stdout, NULL, _IOLBF, 0);
    return true;
}

static void handle_ai_event(
    UNUSED const zappy_server_t *server,
    UNUSED const int interlocutor,
    UNUSED const char *message)
{
    printf("\033[33mNot implemented yet\033[0m\n");
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

static void handle_first_connection(
    zappy_server_t *server,
    const int interlocutor,
    const char *message)
{
    if (!strcmp(message, "GRAPHIC\n")) {
        gui_t *gui = calloc(1, sizeof(gui_t));
        if (!gui)
            return;

        gui->fd = interlocutor;
        TAILQ_INSERT_TAIL(&server->guis, gui, entries);
        printf("New GUI connected\n");
        mct(server, interlocutor, NULL);
        return;
    }
    team_t *team = calloc(1, sizeof(team_t));
    if (!team)
        return;

    team->id = TAILQ_EMPTY(&server->teams) ? 1
        : TAILQ_LAST(&server->teams, teamhead)->id + 1;
    strncpy(team->name, message, 64);
    TAILQ_INSERT_TAIL(&server->teams, team, entries);

    ai_t *ai = calloc(1, sizeof(ai_t));
    if (!ai)
        return;

    ai->fd = interlocutor;
    ai->team = team;
    TAILQ_INSERT_TAIL(&server->ais, ai, entries);
    printf("New AI connected\n");
    protocol_server_send_message(server->socket, interlocutor,
        "%i\n", server->clients_nb);
    protocol_server_send_message(server->socket, interlocutor,
        " %i %i\n", server->width, server->height);
}

static bool handle_payload(
    zappy_server_t *server)
{
    protocol_payload_t *payload;
    protocol_connection_t *connection;
    char *message;

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

    while (!TAILQ_EMPTY(&server->socket->payloads)) {
        payload = TAILQ_FIRST(&server->socket->payloads);
        TAILQ_REMOVE(&server->socket->payloads, payload, entries);
        printf("Received message from %d\n", payload->fd);
        message = protocol_receive_message(payload);
        if (!message)
            return false;
        switch (get_connection_by_fd(server, payload->fd)) {
            case CONNECTION_AI:
                handle_ai_event(server, payload->fd, message);
                break;
            case CONNECTION_GUI:
                handle_gui_event(server, payload->fd, message);
                break;
            case CONNECTION_UNKNOWN:
                handle_first_connection(server, payload->fd, message);
                break;
            default:
                break;
        }
        free(message);
        free(payload);
    }
    return true;
}

bool zappy_server(zappy_server_t *server)
{
    if (!server || server->port < 1024
        || server->width <= 0 || server->height <= 0)
        return false;
    display_server(server);
    server->socket = protocol_server_create(server->port);
    if (!server->socket)
        return false;

    server->map = calloc(server->height, sizeof(inventory_t *));
    if (!server->map)
        return false;
    for (uint16_t y = 0; y < server->height; ++y) {
        server->map[y] = calloc(server->width, sizeof(inventory_t));
        if (!server->map[y])
            return false;
        for (uint16_t x = 0; x < server->width; ++x) {
            server->map[y][x] = (inventory_t){ .food = 0, .linemate = 0,
                .deraumere = 0, .sibur = 0, .mendiane = 0, .phiras = 0,
                .thystame = 0 };
        }
    }

    while (protocol_server_is_open()) {
        protocol_server_listen(server->socket);
        if (!handle_payload(server))
            return false;
    }
    return true;
}
