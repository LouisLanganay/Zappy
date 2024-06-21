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
 * @brief Update the action time of a command
 *
 * @param server The server_t struct
 * @param message The message to update
 *
 * @note Update the action time of a command
 */
void update_cmd_action_time(
    const zappy_server_t *server,
    const char message[1024]
);

/**
 * @brief Add food to the map
 *
 * @param server The server_t struct
 * @param x The x position of the food
 * @param y The y position of the food
 *
 * @note Add food to the map
 */
void add_food(zappy_server_t *server, uint16_t x, uint16_t y);

/**
 * @brief Add linemate to the map
 *
 * @param server The server_t struct
 * @param x The x position of the linemate
 * @param y The y position of the linemate
 *
 * @note Add linemate to the map
 */
void add_linemate(zappy_server_t *server, uint16_t x, uint16_t y);

/**
 * @brief Add deraumere to the map
 *
 * @param server The server_t struct
 * @param x The x position of the deraumere
 * @param y The y position of the deraumere
 *
 * @note Add deraumere to the map
 */
void add_deraumere(zappy_server_t *server, uint16_t x, uint16_t y);

/**
 * @brief Add sibur to the map
 *
 * @param server The server_t struct
 * @param x The x position of the sibur
 * @param y The y position of the sibur
 *
 * @note Add sibur to the map
 */
void add_sibur(zappy_server_t *server, uint16_t x, uint16_t y);

/**
 * @brief Add mendiane to the map
 *
 * @param server The server_t struct
 * @param x The x position of the mendiane
 * @param y The y position of the mendiane
 *
 * @note Add mendiane to the map
 */
void add_mendiane(zappy_server_t *server, uint16_t x, uint16_t y);

/**
 * @brief Add phiras to the map
 *
 * @param server The server_t struct
 * @param x The x position of the phiras
 * @param y The y position of the phiras
 *
 * @note Add phiras to the map
 */
void add_phiras(zappy_server_t *server, uint16_t x, uint16_t y);

/**
 * @brief Add thystame to the map
 *
 * @param server The server_t struct
 * @param x The x position of the thystame
 * @param y The y position of the thystame
 *
 * @note Add thystame to the map
 */
void add_thystame(zappy_server_t *server, uint16_t x, uint16_t y);

static const struct {
    void (*func)(
        zappy_server_t *server,
        uint16_t x,
        uint16_t y);
} ressources[] = {
    {add_food},
    {add_linemate},
    {add_deraumere},
    {add_sibur},
    {add_mendiane},
    {add_phiras},
    {add_thystame}
};

#endif /* !GAME_H_ */
