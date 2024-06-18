/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** left
*/

#include <stdio.h>

#include "server/ai_header.h"

void left(
    zappy_server_t *server,
    ai_t *ai,
    UNUSED const char *message)
{
    switch (ai->orientation) {
        case NORTH:
            ai->orientation = WEST;
            break;
        case WEST:
            ai->orientation = SOUTH;
            break;
        case EAST:
            ai->orientation = NORTH;
            break;
        case SOUTH:
            ai->orientation = EAST;
            break;
    }
    protocol_server_send(server->socket, ai->fd, "ok");
}
