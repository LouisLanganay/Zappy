/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** AI
*/

#ifndef AI_H
    #define AI_H

    #include <stddef.h>

    #include "server.h"

/**
 * @brief Move player up one tile
 *
 * @param server The server_t struct
 * @param ai The associated ai struct
 * @param message The message of the command
 *
 * @note Call forward
 * @note Move the player one tile up
 */
void forward(
    const zappy_server_t *server,
    ai_t *ai,
    const char *message);

/**
 * @brief Turn player 90° right
 *
 * @param server The server_t struct
 * @param ai The associated ai struct
 * @param message The message of the command
 *
 * @note Call right
 * @note Turn player 90° right
 */
void right(
    const zappy_server_t *server,
    ai_t *ai,
    const char *message);

/**
 * @brief Turn player 90° left
 *
 * @param server The server_t struct
 * @param ai The associated ai struct
 * @param message The message of the command
 *
 * @note Call left
 * @note Turn player 90° left
 */
void left(
    const zappy_server_t *server,
    ai_t *ai,
    const char *message);

/**
 * @brief Look tiles arround player
 *
 * @param server The server_t struct
 * @param ai The associated ai struct
 * @param message The message of the command
 *
 * @note Call look
 * @note Look tiles arround player
 */
void look(
    const zappy_server_t *server,
    ai_t *ai,
    const char *message);

/**
 * @brief Display player inventory
 *
 * @param server The server_t struct
 * @param ai The associated ai struct
 * @param message The message of the command
 *
 * @note Call inventory
 * @note Display player inventory
 */
void inventory(
    const zappy_server_t *server,
    ai_t *ai,
    const char *message);

/**
 * @brief Broadcast player text
 *
 * @param server The server_t struct
 * @param ai The associated ai struct
 * @param message The message of the command
 *
 * @note Call Broadcast text
 * @note Broadcast player text
 */
void broadcast_text(
    const zappy_server_t *server,
    ai_t *ai,
    const char *message);

/**
 * @brief Display number of team with unused slot
 *
 * @param server The server_t struct
 * @param ai The associated ai struct
 * @param message The message of the command
 *
 * @note Call Connect_nbr
 * @note Display number of team with unused slot
 */
void connect_nbr(
    const zappy_server_t *server,
    ai_t *ai,
    const char *message);

/**
 * @brief Fork a player
 *
 * @param server The server_t struct
 * @param ai The associated ai struct
 * @param message The message of the command
 *
 * @note Call Fork
 * @note Fork the player
 */
void exec_fork(
    const zappy_server_t *server,
    ai_t *ai,
    const char *message);

/**
 * @brief Eject a players from a tile
 *
 * @param server The server_t struct
 * @param ai The associated ai struct
 * @param message The message of the command
 *
 * @note Call Eject
 * @note Eject players from this tile
 */
void eject(
    const zappy_server_t *server,
    ai_t *ai,
    const char *message);

/**
 * @brief Alert on a player death
 *
 * @param server The server_t struct
 * @param ai The associated ai struct
 * @param message The message of the command
 *
 */
void death(
    const zappy_server_t *server,
    ai_t *ai,
    const char *message);

/**
 * @brief Take an object
 *
 * @param server The server_t struct
 * @param ai The associated ai struct
 * @param message The message of the command
 *
 */
void take_object(
    const zappy_server_t *server,
    ai_t *ai,
    const char *message);

/**
 * @brief Set an object down
 *
 * @param server The server_t struct
 * @param ai The associated ai struct
 * @param message The message of the command
 *
 */
void set_object(
    const zappy_server_t *server,
    ai_t *ai,
    const char *message);

/**
 * @brief Start incantation
 *
 * @param server The server_t struct
 * @param ai The associated ai struct
 * @param message The message of the command
 *
 */
void incantation(
    const zappy_server_t *server,
    ai_t *ai,
    const char *message);

static const struct {
    const char *cmd;
    void (*func)(
        const zappy_server_t *server,
        ai_t *ai,
        const char *message);
} ai_cmds[] = {
    {"Forward", forward},
    {"Right", right},
    {"Left", left},
    {"Look", look},
    {"Inventory", inventory},
    {"Broadcast", broadcast_text},
    {"Connect_nbr", connect_nbr},
    {"Fork", exec_fork},
    {"Eject", eject},
    {"Take", take_object},
    {"Set", set_object},
    {"Incantation", incantation},
    {NULL, NULL}
};

#endif //AI_H
