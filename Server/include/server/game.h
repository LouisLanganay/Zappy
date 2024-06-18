/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** game
*/

#ifndef GAME_H_
    #define GAME_H_


    #include <stddef.h>
    #include <stdio.h>

    #include "server.h"

/**
 * @brief Update the game
 *
 * @param server The server_t struct
 *
 * @note Game loop
 */
void game_update(zappy_server_t *server);

/**
 * @brief Spawns ressources every 20 game time unit
 *
 * @param server The server_t struct
 *
 * @note Function that is here to spawns the ressources on the map
 */
void trigger_meteor(zappy_server_t *server);

/**
 * @brief handle ai cmds
 *
 * @param server The server_t struct
 *
 * @note Function that is here to handle the ai cmds
 */
void handle_ai_cmds(zappy_server_t *server);

#endif /* !GAME_H_ */
