/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** game_update
*/

#include "server/game.h"
#include "server/gui.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

static void waiting_time(
    zappy_server_t *server,
    int i,
    struct timespec *curr_time,
    double elapsed_time)
{
    int lever = 0;
    double time_to_wait = 0;
    double curr_time_in_sec = 0;
    double last_update_in_sec = 0;

    if (lever == 0) {
        time_to_wait = server->cmd[i]->action_time / server->freq;
        lever = 1;
    }
    curr_time_in_sec = curr_time->tv_sec + (curr_time->tv_nsec / 1000000000);
    last_update_in_sec = server->last_update.tv_sec +
    (server->last_update.tv_nsec / 1000000000);
    elapsed_time = curr_time_in_sec - last_update_in_sec;
    if (elapsed_time >= time_to_wait) {
        server->cmd[i]->active = false;
    }
    if (elapsed_time >= 20.0) {
        trigger_meteor(server);
        server->last_update = *curr_time;
    }
}

static bool handle_time(zappy_server_t *server)
{
    struct timespec *curr_time = malloc(sizeof(struct timespec));
    double elapsed_time = 0;
    double game_time_elapsed = 0;

    clock_gettime(CLOCK_REALTIME, curr_time);
    for (int i = 0; i < 12; i++) {
        if (server->cmd[i]->active) {
            waiting_time(server, i, curr_time, elapsed_time);
        }
    }
    elapsed_time = difftime(curr_time->tv_sec, server->last_update.tv_sec);
    game_time_elapsed = elapsed_time / server->freq;
    if (game_time_elapsed < 20.0) {
        return false;
    }
    server->last_update = *curr_time;
    return true;
}

static void player_nutrition(
    zappy_server_t *server,
    ai_t *ai)
{
    if (ai->inventory.food >= 1) {
        ai->inventory.food -= 1;
    } else {
        TAILQ_REMOVE(&server->ais, ai, entries);
    }
}

static void handle_players_food(zappy_server_t *server)
{
    ai_t *ai;
    double player_life = 0;

    TAILQ_FOREACH(ai, &server->ais, entries) {
        if (ai->team == NULL)
            continue;
        player_life = (double)((clock() - ai->player_life)) / CLOCKS_PER_SEC;
        if (player_life >= (double)((FOOD_SATURATION / server->freq))) {
            player_nutrition(server, ai);
            ai->player_life = clock();
        }
    }
}

static void handle_eggs(zappy_server_t *server)
{
    egg_t *egg;
    double egg_life = 0;

    TAILQ_FOREACH(egg, &server->eggs, entries) {
        egg_life = (double)((clock() - egg->lay_time)) / CLOCKS_PER_SEC;
        if (egg_life >= (double)((EGG_LAY_TIME / server->freq))) {
            TAILQ_REMOVE(&server->eggs, egg, entries);
            free(egg);
        }
    }
}

void game_update(zappy_server_t *server)
{
    if (handle_time(server))
        trigger_meteor(server);
    handle_players_food(server);
    handle_eggs(server);
}
