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

static const struct {
    const char *cmd;
    void (*func)(
        const zappy_server_t *server,
        int interlocutor,
        const char *message);
} ai_cmds[] = {
    {NULL, NULL}
};

#endif //AI_H
