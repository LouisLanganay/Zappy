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
#include "server.h"


static void fill_cmds(zappy_server_t *server)
{
    server->cmd[6]->active = false;
    server->cmd[6]->cmd = "Connect_nbr";
    server->cmd[6]->action_time = 0;
    server->cmd[7]->active = false;
    server->cmd[7]->cmd = "Fork";
    server->cmd[7]->action_time = 42;
    server->cmd[8]->active = false;
    server->cmd[8]->cmd = "Eject";
    server->cmd[8]->action_time = 7;
    server->cmd[9]->active = false;
    server->cmd[9]->cmd = "Take";
    server->cmd[9]->action_time = 7;
    server->cmd[10]->active = false;
    server->cmd[10]->cmd = "Set";
    server->cmd[10]->action_time = 7;
    server->cmd[11]->active = false;
    server->cmd[11]->cmd = "Incantation";
    server->cmd[11]->action_time = 300;
}

static void fill_cmd(zappy_server_t *server)
{
    server->cmd = malloc(sizeof(cmd_t *) * 12);
    server->cmd[0]->active = false;
    server->cmd[0]->cmd = "Forward";
    server->cmd[0]->action_time = 7;
    server->cmd[1]->active = false;
    server->cmd[1]->cmd = "Right";
    server->cmd[1]->action_time = 7;
    server->cmd[2]->active = false;
    server->cmd[2]->cmd = "Left";
    server->cmd[2]->action_time = 7;
    server->cmd[3]->active = false;
    server->cmd[3]->cmd = "Look";
    server->cmd[3]->action_time = 7;
    server->cmd[4]->active = false;
    server->cmd[4]->cmd = "Inventory";
    server->cmd[4]->action_time = 1;
    server->cmd[5]->active = false;
    server->cmd[5]->cmd = "Broadcast";
    server->cmd[5]->action_time = 7;
    fill_cmds(server);
}

void server_create(
    zappy_server_t *server)
{
    *server = (zappy_server_t){ .port = 4242, .width = 10, .height = 10 };
    server->last_update = (struct timespec){ .tv_sec = 0, .tv_nsec = 0 };
    fill_cmd(server);
    TAILQ_INIT(&server->ais);
    TAILQ_INIT(&server->teams);
    TAILQ_INIT(&server->guis);
}

static bool server_set_socket(
    zappy_server_t *server)
{
    server->socket = protocol_server_create(server->port);
    return server->socket;
}

static bool server_set_map(
    zappy_server_t *server)
{
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
    ai_t *ai;

    if (!server || server->port < 1024
        || server->width <= 0 || server->height <= 0
        || server->clients_nb <= 0 || server->freq <= 0
        || !server_set_socket(server) || !server_set_map(server))
        return false;
    display_server(server);
    trigger_meteor(server);
    TAILQ_FOREACH(ai, &server->ais, entries)
        ai->player_life = 126;
    while (protocol_server_is_open()) {
        game_update(server);
        protocol_server_listen(server->socket);
        if (!handle_payload(server))
            return false;
    }
    return true;
}
