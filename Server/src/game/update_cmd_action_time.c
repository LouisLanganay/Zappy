/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** update_cmd_action_time
*/

#include <string.h>

#include "server/game.h"

void update_cmd_action_time(
    const zappy_server_t *server,
    const char message[DATA_SIZE])
{
    for (int i = 0; server->cmd[i]; i++)
        if (strncmp(message, server->cmd[i]->cmd, strlen(server->cmd[i]->cmd)) == 0) {
            server->cmd[i]->active = true;
            return;
        }
}
