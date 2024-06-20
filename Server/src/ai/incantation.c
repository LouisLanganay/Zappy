/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** incantation
*/

#include <stdio.h>
#include <stdlib.h>

#include "server/ai_header.h"
#include "server/gui.h"

static incantation_t *create_incantation(
    ai_t *ai)
{
    incantation_t *elm = calloc(1, sizeof(incantation_t));

    if (!elm)
        return NULL;
    elm->ai = ai;
    ai->is_incantate = true;
    return elm;
}

static bool notify(
    const zappy_server_t *server,
    const ai_t *ai)
{
    uint16_t count = 0;
    const ai_t **ais;

    for (const incantation_t *elm = TAILQ_FIRST(&ai->incantations); elm;
        elm = TAILQ_NEXT(elm, entries))
        count++;
    ais = calloc(count + 1, sizeof(ai_t *));
    if (!ais)
        return false;
    count = 0;
    for (const incantation_t *elm = TAILQ_FIRST(&ai->incantations); elm;
        elm = TAILQ_NEXT(elm, entries)) {
        protocol_server_send(server->socket, elm->ai->fd,
            "Elevation underway");
        ais[count] = elm->ai;
        count++;
    }
    pic(server, ais);
    free(ais);
    return true;
}

static void clean_incantations(
    ai_t *ai)
{
    for (const incantation_t *elm = TAILQ_FIRST(&ai->incantations); elm;
        elm = TAILQ_FIRST(&ai->incantations)) {
        elm->ai->is_incantate = false;
        TAILQ_REMOVE(&ai->incantations, elm, entries);
    }
}

static bool create_incantations(
    const zappy_server_t *server,
    ai_t *ai)
{
    uint16_t count = level_need[ai->level - 1].resources[0] - 1;

    TAILQ_INSERT_TAIL(&ai->incantations, create_incantation(ai), entries);
    for (ai_t *elm = TAILQ_FIRST(&server->ais); elm;
        elm = TAILQ_NEXT(elm, entries)) {
        if (elm->fd != ai->fd && elm->level == ai->level &&
            elm->pos.x == ai->pos.x && elm->pos.y == ai->pos.y &&
            elm->is_incantate == false && elm->inventory.food > 0) {
            TAILQ_INSERT_TAIL(&ai->incantations, create_incantation(elm),
                entries);
            count--;
        }
    }
    if (count > 0) {
        clean_incantations(ai);
        return false;
    }
    return notify(server, ai);
}

static bool check_incantations(
    const ai_t *ai)
{
    incantation_t *elm;
    uint16_t count = 1;

    TAILQ_FOREACH(elm, &ai->incantations, entries)
        if (elm->ai->fd != ai->fd
            && elm->ai->pos.x == ai->pos.x && elm->ai->pos.y == ai->pos.y
            && elm->ai->level == ai->level && ai->inventory.food > 0)
            count++;
    return count >= level_need[ai->level - 1].resources[0];
}

bool can_incantation(
    const zappy_server_t *server,
    ai_t *ai,
    UNUSED const char *message)
{
    if (ai->level == 8)
        return false;
    for (uint8_t i = 1; i < 7; i++)
        if (server->map[ai->pos.x][ai->pos.y].resources[i] <
            level_need[ai->level - 1].resources[i])
            return false;
    return TAILQ_EMPTY(&ai->incantations)
        ? create_incantations(server, ai)
        : check_incantations(ai);
}

void incantation(
    zappy_server_t *server,
    ai_t *ai,
    UNUSED const char *message)
{
    incantation_t *elm;

    if (!can_incantation(server, ai, "")) {
        TAILQ_FOREACH(elm, &ai->incantations, entries)
            protocol_server_send(server->socket, elm->ai->fd, "ko");
        return;
    }
    for (uint8_t i = 1; i < 7; i++)
        server->map[ai->pos.x][ai->pos.y].resources[i] -=
            level_need[ai->level - 1].resources[i];
    TAILQ_FOREACH(elm, &ai->incantations, entries)
        if (elm->ai->fd != ai->fd
            && elm->ai->pos.x == ai->pos.x && elm->ai->pos.y == ai->pos.y
            && elm->ai->level == ai->level && ai->inventory.food > 0)
            elm->ai->level++;
    pie(server, ai);
    clean_incantations(ai);
}
