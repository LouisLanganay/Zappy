/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** left
*/

#include "server/ai_header.h"
#include "server/gui.h"

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
    server_send(server, ai->fd, "ok");
    server_ppo(server, ai);
}
