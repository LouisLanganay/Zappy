/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** right
*/

#include "server/ai_header.h"
#include "server/gui.h"

void right(
    zappy_server_t *server,
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
    server_send(server, ai->fd, "ok");
    server_ppo(server, ai);
}
