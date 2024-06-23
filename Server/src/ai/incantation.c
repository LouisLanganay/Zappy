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
    ai->state = INCANTATE;
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
    zappy_server_t *server,
    ai_t *ai)
{
    incantation_t *next;

    if (TAILQ_EMPTY(&ai->incantations))
        return;
    for (incantation_t *elm = TAILQ_FIRST(&ai->incantations); elm;
        elm = next) {
        next = TAILQ_NEXT(elm, entries);
        if (elm->ai->state == INCANTATE)
            elm->ai->state = ALIVE;
        if (elm->ai->level == 8) {
            server->is_game_end = true;
            seg(server, elm->ai->team);
        }
        TAILQ_REMOVE(&ai->incantations, elm, entries);
        free(elm);
    }
}

static bool create_incantations(
    zappy_server_t *server,
    ai_t *ai)
{
    incantation_t *elm = create_incantation(ai);

    if (!elm)
        return false;
    TAILQ_INSERT_TAIL(&ai->incantations, elm, entries);
    for (ai_t *ai_elm = TAILQ_FIRST(&server->ais); ai_elm;
        ai_elm = TAILQ_NEXT(ai_elm, entries)) {
        if (ai_elm->fd == ai->fd || ai_elm->level != ai->level
            || ai_elm->pos.x != ai->pos.x || ai_elm->pos.y != ai->pos.y
            || ai_elm->state == INCANTATE || ai_elm->state == DEAD)
            continue;
        elm = create_incantation(ai_elm);
        if (!elm)
            return false;
        TAILQ_INSERT_TAIL(&ai->incantations, elm, entries);
    }
    if (!level_need[ai->level - 1].resources[0] - 1)
        return notify(server, ai);
    clean_incantations(server, ai);
    return false;
}

static bool check_incantations(
    const ai_t *ai)
{
    incantation_t *elm;
    uint16_t count = 1;

    TAILQ_FOREACH(elm, &ai->incantations, entries)
        if (elm->ai->fd != ai->fd
            && elm->ai->pos.x == ai->pos.x && elm->ai->pos.y == ai->pos.y
            && elm->ai->level == ai->level && elm->ai->state == INCANTATE)
            count++;
    return count >= level_need[ai->level - 1].resources[0];
}

bool can_incantation(
    zappy_server_t *server,
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
        clean_incantations(server, ai);
        return;
    }
    for (uint8_t i = 1; i < 7; i++)
        server->map[ai->pos.x][ai->pos.y].resources[i] -=
            level_need[ai->level - 1].resources[i];
    TAILQ_FOREACH(elm, &ai->incantations, entries)
        if (elm->ai->pos.x == ai->pos.x && elm->ai->pos.y == ai->pos.y
            && elm->ai->level == ai->level && ai->state != DEAD) {
            elm->ai->level++;
            protocol_server_send(server->socket, elm->ai->fd,
                "Current level: %d", elm->ai->level);
        }
    pie(server, ai);
    clean_incantations(server, ai);
}
