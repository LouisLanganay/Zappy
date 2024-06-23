/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** game
*/

#include <stdlib.h>

#include "server/ai_header.h"
#include "server/game.h"

static void update_ai_life_span(
    zappy_server_t *server)
{
    for (ai_t *ai = TAILQ_FIRST(&server->ais); ai;
        ai = TAILQ_NEXT(ai, entries)) {
        ai->life_span--;
        if (ai->life_span > 0)
            continue;
        if (ai->inventory.food >= 1) {
            ai->inventory.food -= 1;
            continue;
        }
        TAILQ_REMOVE(&server->ais, ai, entries);
        death(server, ai);
    }
}

static void update_ai(
    zappy_server_t *server)
{
    ai_cmd_t *cmd;

    for (ai_t *ai = TAILQ_FIRST(&server->ais); ai;
        ai = TAILQ_NEXT(ai, entries)) {
        if (ai->state == INCANTATE || ai->state == DEAD
            || TAILQ_EMPTY(&ai->commands))
            continue;
        cmd = TAILQ_FIRST(&ai->commands);
        cmd->time--;
        if (cmd->time > 0)
            continue;
        TAILQ_REMOVE(&ai->commands, cmd, entries);
        cmd->func(server, ai, cmd->cmd);
        free(cmd);
    }
}

void update_game(
    zappy_server_t *server)
{
    struct timespec curr_time;
    uint16_t diff;

    clock_gettime(CLOCK_REALTIME, &curr_time);
    diff = ((curr_time.tv_sec - server->last_update.tv_sec) * 1000000000L
        + (curr_time.tv_nsec - server->last_update.tv_nsec))
        / (1000000000L / server->freq);
    if (diff == 0)
        return;
    server->last_update = curr_time;
    for (; diff > 0; --diff) {
        update_map(server);
        update_ai_life_span(server);
        update_ai(server);
    }
}
