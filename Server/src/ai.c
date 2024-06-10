/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ai
*/

#include <stddef.h>

#include "server.h"

void ai_send_to_all(
    const zappy_server_t *server,
    const char *message)
{
    const ai_t *ai;

    TAILQ_FOREACH(ai, &server->ais, entries)
        protocol_server_send(server->socket, ai->fd, message);
}

ai_t *ai_get_by_id(
    const zappy_server_t *server,
    const uint16_t id)
{
    ai_t *ai;

    TAILQ_FOREACH(ai, &server->ais, entries)
        if (ai->id == id)
            return ai;
    return NULL;
}

ai_t *ai_get_by_fd(
    const zappy_server_t *server,
    const int fd)
{
    ai_t *ai;

    TAILQ_FOREACH(ai, &server->ais, entries)
        if (ai->fd == fd)
            return ai;
    return NULL;
}

uint16_t ai_get_nb_by_pos(
    const zappy_server_t *server,
    const vector2_t *pos)
{
    uint16_t nb = 0;
    ai_t *ai;

    TAILQ_FOREACH(ai, &server->ais, entries)
        if (ai->pos.x == pos->x && ai->pos.y == pos->y)
            nb++;
    return nb;
}
