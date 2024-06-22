/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** forward
*/

#include "server/ai_header.h"
#include "server/gui.h"

void forward(
    zappy_server_t *server,
    ai_t *ai,
    UNUSED const char *message)
{
    switch (ai->orientation) {
        case NORTH:
            ai->pos.y = (ai->pos.y + server->height - 1) % server->height;
            break;
        case WEST:
            ai->pos.x = (ai->pos.x + server->width - 1) % server->width;
            break;
        case EAST:
            ai->pos.x = (ai->pos.x + 1) % server->width;
            break;
        case SOUTH:
            ai->pos.y = (ai->pos.y + 1) % server->height;
            break;
    }
    protocol_server_send(server->socket, ai->fd, "ok");
    server_ppo(server, ai);
}
