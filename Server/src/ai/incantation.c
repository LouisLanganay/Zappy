/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** incantation
*/

#include <stdio.h>
#include <string.h>

#include "server/ai_header.h"

static uint8_t get_same_player_nb(
    const zappy_server_t *server,
    const ai_t *ai)
{
    uint8_t same_player = 0;
    ai_t *n_ai;

    TAILQ_FOREACH(n_ai, &server->ais, entries) {
        if ((n_ai->pos.x == ai->pos.x && n_ai->pos.y == ai->pos.y) &&
            strcmp(n_ai->team->name, ai->team->name) == 0 &&
            n_ai->level == ai->level) {
            same_player++;
        }
    }
    return same_player;
}

bool can_incantation(
    const zappy_server_t *server,
    const ai_t *ai)
{
    if (ai->level == 8)
        return false;
    if (get_same_player_nb(server, ai) <
        level_need[ai->level - 1].resources[0])
        return false;
    for (uint8_t i = 1; i < 7; i++) {
        if (server->map[ai->pos.x][ai->pos.y].resources[i] <
            level_need[ai->level - 1].resources[i])
            return false;
    }
    return true;
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
            strcmp(n_ai->team->name, ai->team->name) == 0 &&
            n_ai->level == ai->level) {
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
