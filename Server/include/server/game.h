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
void trigger_meteor(const zappy_server_t *server);

/**
 * @brief Update the action time of a command
 *
 * @param server The server_t struct
 * @param message The message to update
 *
 * @note Update the action time of a command
 */
void update_cmd_action_time(
    const zappy_server_t *server,
    const char message[DATA_SIZE]
);

#endif /* !GAME_H_ */
