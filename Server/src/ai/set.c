/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** set
*/

#include <string.h>

#include "server/ai_header.h"

void set(
    const zappy_server_t *server,
    ai_t *ai,
    const char *message)
{
    for (uint8_t i = 0; i < 7; i++) {
        if (!strcmp(RESSOURCES_NAMES[i], message + 1)
            || !ai->inventory.resources[i]) {
            protocol_server_send(server->socket, ai->fd, "ko");
            return;
            }
        server->map[ai->pos.y][ai->pos.x].resources[i] += 1;
        ai->inventory.resources[i] -= 1;
        protocol_server_send(server->socket, ai->fd, "ok");
    }
}
