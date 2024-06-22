/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** eject
*/

#include <stdlib.h>

#include "server/ai_header.h"
#include "server/gui.h"

static orientation_t convert_orientation(
    const orientation_t orientation)
{
    return (orientation_t[]){ WEST, SOUTH, EAST, NORTH }[orientation - 1];
}

static void eject_egg(
    zappy_server_t *server,
    const ai_t *ai,
    bool *ejected)
{
    egg_t *next;

    for (egg_t *egg = TAILQ_FIRST(&server->eggs); egg; egg = next) {
        next = TAILQ_NEXT(egg, entries);
        if (egg->pos.x != ai->pos.x || egg->pos.y != ai->pos.y)
            continue;
        TAILQ_REMOVE(&server->eggs, egg, entries);
        edi(server, egg->id);
        free(egg);
        *ejected = true;
    }
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
    bool ejected = false;

    TAILQ_FOREACH(target, &server->ais, entries)
        if (target->fd != ai->fd
            && target->pos.x == ai->pos.x && target->pos.y == ai->pos.y) {
            protocol_server_send(server->socket, ai->fd, "eject: %i",
                (uint8_t[]){ 8, 6, 4, 2 }[(convert_orientation(WEST)
                    + convert_orientation(NORTH) - 1) % 4]);
            ejected = true;
            pex(server, target);
        }
    eject_egg(server, ai, &ejected);
    if (ejected)
        protocol_server_send(server->socket, ai->fd, "ok");
    else
        protocol_server_send(server->socket, ai->fd, "ko");
}
