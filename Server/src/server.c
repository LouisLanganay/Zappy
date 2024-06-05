/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** server
*/

#include <stdlib.h>
#include <stdio.h>

#include "server.h"

#include <string.h>

void server_create(
    zappy_server_t *server)
{
    *server = (zappy_server_t){ .port = 4242, .width = 10, .height = 10 };
    TAILQ_INIT(&server->ais);
    TAILQ_INIT(&server->teams);
    TAILQ_INIT(&server->guis);
}

static bool server_init(
    zappy_server_t *server)
{
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
    return true;
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

bool zappy_server(zappy_server_t *server)
{
    if (!server || server->port < 1024
        || server->width <= 0 || server->height <= 0
        || server->clients_nb <= 0 || server->freq <= 0
        || !server_init(server))
        return false;
    display_server(server);
    while (protocol_server_is_open()) {
        protocol_server_listen(server->socket);
        if (!handle_payload(server))
            return false;
    }
    return true;
}