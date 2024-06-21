/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** update_cmd_action_time
*/

#include "server/game.h"
#include <stdlib.h>
#include <string.h>

void update_cmd_action_time(
    const zappy_server_t *server,
    const char message[1024]
)
{
    uint8_t cmd_lenght;

    for (int i = 0; server->cmd[i] != NULL; i++) {
        cmd_lenght = strlen(server->cmd[i]->cmd);
        if (strncmp(message, server->cmd[i]->cmd, cmd_lenght) == 0) {
            server->cmd[i]->active = true;
            return;
        }
    }
}
