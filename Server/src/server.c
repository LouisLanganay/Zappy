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

void server_init(zappy_server_t *server)
{
    *server = (zappy_server_t){ .port = 4242, .width = 10, .height = 10 };
    TAILQ_INIT(&server->ais);
    TAILQ_INIT(&server->teams);
    TAILQ_INIT(&server->guis);
}

static bool display_server(const zappy_server_t *server)
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
    if (printf("\nverbose = %d"
        "\n==================================================\n",
        server->verbose) < 0)
        return false;
    fflush(stdout);
    setvbuf(stdout, NULL, _IOLBF, 0);
    return true;
}

static void handle_payload(const zappy_server_t *server,
    const protocol_payload_t *payload)
{
    switch (payload->packet.type) {
    case EVT_MSZ:
    case EVT_BCT:
    case EVT_MCT:
    case EVT_TNA:
    case EVT_PPO:
    case EVT_PLV:
    case EVT_PIN:
        gui_cmds[payload->packet.type].func(server, payload);
        break;
    default:
        suc(server, payload);
        break;
    }
}

bool zappy_server(zappy_server_t *server)
{
    protocol_payload_t *payload;

    if (!server || server->port < 1024
        || server->width <= 0 || server->height <= 0)
        return false;
    display_server(server);
    server->socket = protocol_server_create(server->port);
    if (!server->socket)
        return false;
    while (protocol_server_is_open()) {
        protocol_server_listen(server->socket);
        while (!TAILQ_EMPTY(&server->socket->payloads)) {
            payload = TAILQ_FIRST(&server->socket->payloads);
            TAILQ_REMOVE(&server->socket->payloads, payload, entries);
            handle_payload(server, payload);
            free(payload);
        }
    }
    return true;
}
