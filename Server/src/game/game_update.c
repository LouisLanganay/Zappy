/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** game_update
*/

#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "server/game.h"

static void waiting_time(
    zappy_server_t *server,
    const int i,
    struct timespec *curr_time)
{
    double elapsed_time = (curr_time->tv_sec + curr_time->tv_nsec / 1000000000)
        - (server->last_update.tv_sec + server->last_update.tv_nsec
        / 1000000000);
    if (elapsed_time >= server->cmd[i]->action_time / server->freq)
        server->cmd[i]->active = false;
    if (elapsed_time >= 20.0) {
        trigger_meteor(server);
        server->last_update = *curr_time;
    }
}

static bool handle_time(
    zappy_server_t *server)
{
    struct timespec *curr_time = malloc(sizeof(struct timespec));

    clock_gettime(CLOCK_REALTIME, curr_time);
    for (uint8_t i = 0; i < 12; i++)
        if (server->cmd[i]->active)
            waiting_time(server, i, curr_time);
    if (difftime(curr_time->tv_sec, server->last_update.tv_sec)
        / server->freq < 20.0)
        return false;
    server->last_update = *curr_time;
    return true;
}

static void player_nutrition(
    zappy_server_t *server,
    ai_t *ai)
{
    if (ai->inventory.food >= 1)
        ai->inventory.food -= 1;
    else
        TAILQ_REMOVE(&server->ais, ai, entries);
}

void game_update(zappy_server_t *server)
{
    ai_t *ai;
    egg_t *egg;

    if (handle_time(server))
        trigger_meteor(server);
    TAILQ_FOREACH(ai, &server->ais, entries)
        if ((clock() - ai->player_life) / CLOCKS_PER_SEC
            >= FOOD_SATURATION / server->freq) {
            player_nutrition(server, ai);
            ai->player_life = clock();
        }
    TAILQ_FOREACH(egg, &server->eggs, entries)
        if ((clock() - egg->lay_time) / CLOCKS_PER_SEC
            >= EGG_LAY_TIME / server->freq) {
            TAILQ_REMOVE(&server->eggs, egg, entries);
            TAILQ_INSERT_TAIL(&server->ais, ai, entries);
            free(egg);
        }
}
