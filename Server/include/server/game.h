/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** game
*/

#ifndef GAME_H_
    #define GAME_H_

    #include "server.h"

void update_game(
    zappy_server_t *server);

void update_map(
    zappy_server_t *server);

bool init_map(
    zappy_server_t *server);

#endif /* !GAME_H_ */
