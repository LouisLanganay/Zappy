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
 * @param interlocutor The fd of the GUI
 * @param message The message of the command
 *
 * @note Call forward
 * @note Move the player one tile up
 */
void forward(
    const zappy_server_t *server,
    int interlocutor,
    const char *message);

/**
 * @brief Turn player 90° right
 *
 * @param server The server_t struct
 * @param interlocutor The fd of the GUI
 * @param message The message of the command
 *
 * @note Call right
 * @note Turn player 90° right
 */
void right(
    const zappy_server_t *server,
    int interlocutor,
    const char *message);


static const struct {
    const char *cmd;
    void (*func)(
        const zappy_server_t *server,
        int interlocutor,
        const char *message);
} ai_cmds[] = {
    {"Forward", forward},
    {"Right", right},
    {NULL, NULL}
};

#endif //AI_H
