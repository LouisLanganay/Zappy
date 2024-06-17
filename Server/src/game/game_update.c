/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** game_update
*/

#include "server/game.h"
#include <time.h>

static bool handle_time(zappy_server_t *server)
{
    struct timespec curr_time;
    double curr_time_in_sec = 0;
    double last_update_in_sec = 0;
    double elapsed_time = 0;
    double game_time_elapsed = 0;

    clock_gettime(CLOCK_REALTIME, &curr_time);
    curr_time_in_sec = curr_time.tv_sec + (curr_time.tv_nsec / 1.0e9);
    last_update_in_sec = server->last_update.tv_sec +
    (server->last_update.tv_nsec / 1.0e9);
    elapsed_time = curr_time_in_sec - last_update_in_sec;
    game_time_elapsed = elapsed_time / server->freq;
    if (game_time_elapsed < 20.0) {
        return false;
    }
    server->last_update = curr_time;
    return true;
}

void game_update(zappy_server_t *server)
{
    if (!handle_time(server))
        return;
    trigger_meteor(server);
}
