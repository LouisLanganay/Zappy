/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** eject
*/

#include <stdlib.h>

#include "server/ai_header.h"
#include "server/gui.h"

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

static uint8_t eject_direction(
    const ai_t *ai,
    const ai_t *target)
{
    return (uint8_t[4][4]){
            { 5, 3, 1, 7 },
            { 7, 5, 3, 1 },
            { 1, 7, 5, 3 },
            { 3, 1, 7, 5 }
        }[target->orientation - 1][ai->orientation - 1];
}

static void eject_target(
    const zappy_server_t *server,
    const ai_t *ai,
    ai_t *target)
{
    switch (ai->orientation) {
        case NORTH:
            target->pos.y = (target->pos.y - 1 + server->height) % server->height;
            break;
        case EAST:
            target->pos.x = (target->pos.x + 1) % server->width;
            break;
        case SOUTH:
            target->pos.y = (target->pos.y + 1) % server->height;
            break;
        case WEST:
            target->pos.x = (target->pos.x - 1 + server->width) % server->width;
            break;
    }
}

//        NORTH EAST  SOUTH WEST
// NORTH  |  5  |  3  |  1  |  7
// EAST   |  7  |  5  |  3  |  1
// SOUTH  |  1  |  7  |  5  |  3
// WEST   |  3  |  1  |  7  |  5
void eject(
    zappy_server_t *server,
    ai_t *ai,
    UNUSED const char *message)
{
    ai_t *target;
    bool ejected = false;

    TAILQ_FOREACH(target, &server->ais, entries) {
        if (target->fd == ai->fd
            || target->pos.x != ai->pos.x || target->pos.y != ai->pos.y)
            continue;
        server_send(server, target->fd,
            "eject: %i", eject_direction(ai, target));
        eject_target(server, ai, target);
        ejected = true;
        pex(server, target);
        server_ppo(server, target);
    }
    eject_egg(server, ai, &ejected);
    if (ejected)
        server_send(server, ai->fd, "ok");
    else
        server_send(server, ai->fd, "ko");
}
