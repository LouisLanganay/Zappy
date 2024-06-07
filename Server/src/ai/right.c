/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** right
*/

#include <stdio.h>

#include "server/ai_header.h"

void right(
    const zappy_server_t *server,
    ai_t *ai,
    UNUSED const char *message)
{
    switch (ai->orientation) {
        case NORTH:
            ai->orientation = EAST;
            break;
        case WEST:
            ai->orientation = NORTH;
            break;
        case EAST:
            ai->orientation = SOUTH;
            break;
        case SOUTH:
            ai->orientation = WEST;
            break;
    }
    protocol_server_send(server->socket, ai->fd, "ok");
}
