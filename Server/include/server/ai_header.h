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
    zappy_server_t *server,
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
    zappy_server_t *server,
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
    zappy_server_t *server,
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
    zappy_server_t *server,
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
    zappy_server_t *server,
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
    zappy_server_t *server,
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
    zappy_server_t *server,
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
    zappy_server_t *server,
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
    zappy_server_t *server,
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
    zappy_server_t *server,
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
void take(
    zappy_server_t *server,
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
void set(
    zappy_server_t *server,
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
    zappy_server_t *server,
    ai_t *ai,
    const char *message);

/**
 * @brief Start incantation
 *
 * @param server The server_t struct
 * @param ai The associated ai struct
 *
 * @note Notify AIs when an incantation fail
 */
void notify_failed_incantation(
    const zappy_server_t *server,
    ai_t *ai);

static const struct {
    const char *cmd;
    void (*func)(
        zappy_server_t *server,
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
    {"Take", take},
    {"Set", set},
    {"Incantation", incantation},
    {NULL, NULL}
};

static const union {
    uint16_t resources[7];
    struct {
        uint16_t players;
        uint16_t linemate;
        uint16_t deraumere;
        uint16_t sibur;
        uint16_t mendiane;
        uint16_t phiras;
        uint16_t thystame;
    };
} level_need[] = {
    {{1, 1, 0, 0, 0, 0, 0}},
    {{2, 1, 1, 1, 0, 0, 0}},
    {{2, 2, 0, 1, 0, 2, 0}},
    {{4, 1, 1, 2, 0, 1, 0}},
    {{4, 1, 2, 1, 3, 0, 0}},
    {{6, 1, 2, 3, 0, 1, 0}},
    {{6, 2, 2, 2, 2, 2, 1}}
};

#endif //AI_H
