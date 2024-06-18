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
    const zappy_server_t *server,
    const ai_t *ai)
{
    for (uint8_t i = 1; i < 7; i++)
        server->map[ai->pos.x][ai->pos.y].resources[i] -= level_need[ai->level - 1].resources[i];
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
