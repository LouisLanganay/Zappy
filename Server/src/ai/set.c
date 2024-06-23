/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** set
*/

#include <string.h>

#include "server/ai_header.h"
#include "server/gui.h"

void set(
    zappy_server_t *server,
    ai_t *ai,
    const char *message)
{
    for (uint8_t i = 0; i < 7; i++) {
        if (strcmp(RESSOURCES_NAMES[i], message + 1))
            continue;
        if (!ai->inventory.resources[i]) {
            server_send(server, ai->fd, "ko");
            return;
        }
        server->ressources.resources[i] += 1;
        server->map[ai->pos.y][ai->pos.x].resources[i] += 1;
        ai->inventory.resources[i] -= 1;
        server_send(server, ai->fd, "ok");
        pdr(server, ai, ai->inventory.resources[i]);
        return;
    }
    server_send(server, ai->fd, "ko");
}
