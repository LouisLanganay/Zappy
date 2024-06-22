/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** server
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "server/game.h"

void server_create(
    zappy_server_t *server)
{
    *server = (zappy_server_t){
        .port = 4242, .width = 10, .height = 10, .freq = 100, .clients_nb = 5
    };
    TAILQ_INIT(&server->eggs);
    TAILQ_INIT(&server->ais);
    TAILQ_INIT(&server->teams);
    TAILQ_INIT(&server->guis);
    srand(time(NULL));
}

static bool init_socket(
    zappy_server_t *server)
{
    server->socket = protocol_server_create(server->port);
    return server->socket;
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
        || server->width < 5 || server->height < 5
        || server->clients_nb < 1 || server->freq < 1
        || !init_map(server) || !init_socket(server))
        return false;
    display_server(server);
    while (protocol_server_is_open()) {
        update_game(server);
        protocol_server_listen(server->socket);
        if (!handle_payload(server))
            return false;
    }
    protocol_server_close(server->socket);
    return true;
}
