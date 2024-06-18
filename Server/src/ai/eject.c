/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** eject
*/

#include "server/ai_header.h"

static orientation_t convert_orientation(
    const orientation_t orientation)
{
    return (orientation_t[]){ WEST, SOUTH, EAST, NORTH }[orientation - 1];
}

//        SOUTH WEST NORTH EAST
// SOUTH  | 6   | 8  | 2   | 4
// WEST   | 4   | 6  | 8   | 2
// NORTH  | 2   | 4  | 6   | 8
// EAST   | 8   | 2  | 4   | 6
void eject(
    zappy_server_t *server,
    ai_t *ai,
    UNUSED const char *message)
{
    ai_t *target;

    TAILQ_FOREACH(target, &server->ais, entries)
        if (target->fd != ai->fd
            && target->pos.x == ai->pos.x && target->pos.y == ai->pos.y) {
            protocol_server_send(server->socket, ai->fd, "eject: %i",
                (uint8_t[]){ 8, 6, 4, 2 }[(convert_orientation(WEST)
                    + convert_orientation(NORTH) - 1) % 4]);
            protocol_server_send(server->socket, ai->fd, "ok");
            return;
        }
    protocol_server_send(server->socket, ai->fd, "ko");
}
