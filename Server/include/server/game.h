/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** game
*/

#ifndef GAME_H_
#define GAME_H_


    #include <stddef.h>

    #include "server.h"

/**
 * @brief Update the game
 *
 * @param server The server_t struct
 *
 * @note Game loop
 */
void game_update(
    zappy_server_t *server);

#endif /* !GAME_H_ */
