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

static incantation_t *create_inc_elm(
    ai_t *ai)
{
    incantation_t *new_elm = calloc(1, sizeof(incantation_t));

    if (!new_elm)
        return NULL;
    new_elm->ai = ai;
    return new_elm;
}

static bool send_start_message(
    const zappy_server_t *server,
    const ai_t *ai)
{
    incantation_t *elm;
    ai_t **ais;
    uint16_t count = 0;
    uint16_t index = 0;

    TAILQ_FOREACH(elm, &ai->incantation_list, entries) {
        protocol_server_send(server->socket, elm->ai->fd,
            "Elevation underway");
        count++;
    }
    ais = calloc(count, sizeof(ai_t *));
    if (!ais)
        return false;
    TAILQ_FOREACH(elm, &ai->incantation_list, entries) {
        ais[index] = elm->ai;
        index++;
    }
    //pic(server, count, ai, ais);
    free(ais);
    return true;
}

static void clean_incantation_list(
    ai_t *ai)
{
    incantation_t *node;

    while (!TAILQ_EMPTY(&ai->incantation_list)) {
        node = TAILQ_FIRST(&ai->incantation_list);
        node->ai->is_incantate = false;
        TAILQ_REMOVE(&ai->incantation_list, node, entries);
    }
}

static bool create_incantation_list(
    zappy_server_t *server,
    ai_t *ai)
{
    ai_t *n_ai;
    int count = level_need[ai->level - 1].resources[0] - 1;

    TAILQ_INSERT_TAIL(&ai->incantation_list, create_inc_elm(ai), entries);
    ai->is_incantate = true;
    TAILQ_FOREACH(n_ai, &server->ais, entries) {
        if (n_ai->fd != ai->fd && n_ai->level == ai->level &&
            n_ai->pos.x == ai->pos.x && n_ai->pos.y == ai->pos.y &&
            n_ai->is_incantate == false) {
            n_ai->is_incantate = true;
            TAILQ_INSERT_TAIL(&ai->incantation_list, create_inc_elm(n_ai),
                entries);
            count--;
        }
    }
    if (count > 0) {
        clean_incantation_list(ai);
        return false;
    }
    return send_start_message(server, ai);
}

static bool verify_incantation_list(ai_t *ai)
{
    incantation_t *node;
    uint16_t count = 1;

    TAILQ_FOREACH(node, &ai->incantation_list, entries) {
        if (node->ai->fd != ai->fd && node->ai->pos.x == ai->pos.x &&
            node->ai->pos.y == ai->pos.y && node->ai->level == ai->level) {
            count++;
        }
    }
    if (count < level_need[ai->level - 1].resources[0])
        return false;
    return true;
}

bool can_incantation(
    zappy_server_t *server,
    ai_t *ai)
{
    if (ai->level == 8)
        return false;
    for (uint8_t i = 1; i < 7; i++) {
        if (server->map[ai->pos.x][ai->pos.y].resources[i] <
            level_need[ai->level - 1].resources[i])
            return false;
    }
    if (TAILQ_EMPTY(&ai->incantation_list)) {
        if (!create_incantation_list(server, ai))
            return false;
    } else {
        if (!verify_incantation_list(ai)) {
            return false;
        }
    }
    return true;
}

void notify_failed_incantation(
    const zappy_server_t *server,
    ai_t *ai)
{
    incantation_t *node;

    if (TAILQ_EMPTY(&ai->incantation_list)) {
        protocol_server_send(server->socket, ai->fd, "ko");
        return;
    }
    TAILQ_FOREACH(node, &ai->incantation_list, entries)
        protocol_server_send(server->socket, node->ai->fd, "ko");
}

static void clean_ressources(
    zappy_server_t *server,
    const ai_t *ai)
{
    for (uint8_t i = 1; i < 7; i++)
        server->map[ai->pos.x][ai->pos.y].resources[i] -=
            level_need[ai->level - 1].resources[i];
}

static void update_data(
    zappy_server_t *server,
    ai_t *ai)
{
    incantation_t *node;

    clean_ressources(server, ai);
    TAILQ_FOREACH(node, &ai->incantation_list, entries) {
        if (node->ai->fd != ai->fd && node->ai->pos.x == ai->pos.x &&
            node->ai->pos.y == ai->pos.y && node->ai->level == ai->level) {
            node->ai->level++;
        }
    }
}

void incantation(
    zappy_server_t *server,
    ai_t *ai,
    UNUSED const char *message)
{
    if (!can_incantation(server, ai)) {
        notify_failed_incantation(server, ai);
        clean_incantation_list(ai);
        pie(server, ai);
        return;
    }
    update_data(server, ai);
    pie(server, ai);
}
