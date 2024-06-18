/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** incantation
*/

#include <stdio.h>

#include "server/ai_header.h"

bool can_incantation(
    UNUSED const zappy_server_t *server,
    UNUSED const ai_t *ai)
{
    return false;
}

static void clean_ressources(
    zappy_server_t *server,
    ai_t *ai)
{
    server->map[ai->pos.x][ai->pos.y].deraumere -= level_t[ai->level - 1].deraumere;
    server->map[ai->pos.x][ai->pos.y].linemate -= level_t[ai->level - 1].linemate;
    server->map[ai->pos.x][ai->pos.y].mendiane -= level_t[ai->level - 1].mendiane;
    server->map[ai->pos.x][ai->pos.y].phiras -= level_t[ai->level - 1].phiras;
    server->map[ai->pos.x][ai->pos.y].sibur -= level_t[ai->level - 1].sibur;
    server->map[ai->pos.x][ai->pos.y].thystame -= level_t[ai->level - 1].thystame;
}

static void update_data(
    zappy_server_t *server,
    ai_t *ai)
{
    ai_t *n_ai;

    clean_ressources(server, ai);
    TAILQ_FOREACH(n_ai, &server->ais, entries) {
        if ((n_ai->pos.x == ai->pos.x && n_ai->pos.y == ai->pos.y) &&
            n_ai->team->name == ai->team->name && n_ai->level == ai->level) {
            n_ai->level++;
        }
    }
}

void incantation(
    zappy_server_t *server,
    ai_t *ai,
    UNUSED const char *message)
{
    if (!can_incantation(server, ai)) {
        protocol_server_send(server->socket, ai->fd, "ko");
        return;
    }
    update_data(server, ai);
}
