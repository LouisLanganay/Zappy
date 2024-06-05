/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** forward
*/

#include <stdio.h>

#include "server/ai_header.h"

void forward(
    const zappy_server_t *server,
    ai_t *ai,
    UNUSED const char *message)
{
    switch(ai->orientation) {
        case(NORTH):
            ai->pos.y = (ai->pos.y + server->height - 1) % server->height;
        case(WEST):
            ai->pos.x = (ai->pos.x + server->width - 1) % server->width;
        case(EAST):
            ai->pos.x = (ai->pos.x + 1) % server->width;
        case(SOUTH):
            ai->pos.y = (ai->pos.y + 1) % server->height;
    }
    protocol_server_send_message(server->socket, ai->fd, "ok\n");
}
