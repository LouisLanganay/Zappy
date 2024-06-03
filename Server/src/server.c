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

static bool handle_payload(
    const zappy_server_t *server)
{
    protocol_payload_t *payload;
    char *message;

    while (!TAILQ_EMPTY(&server->socket->payloads)) {
        payload = TAILQ_FIRST(&server->socket->payloads);
        TAILQ_REMOVE(&server->socket->payloads, payload, entries);
        message = protocol_receive_message(payload);
        if (!message)
            return false;
        handle_gui_event(server, payload->fd, message);
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
    while (protocol_server_is_open()) {
        protocol_server_listen(server->socket);
        if (!handle_payload(server))
            return false;
    }
    return true;
}
