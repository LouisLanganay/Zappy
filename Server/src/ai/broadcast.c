/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** broadcast_text
*/

#include <stdio.h>

#include "server/ai_header.h"

static int get_broadcast_direction(
    const ai_t *emitter,
    const ai_t *target)
{
    const int x = target->pos.x - emitter->pos.x;
    const int y = target->pos.y - emitter->pos.y;

    if (x == 0 && y < 0)
        return (uint8_t[]){5, 7, 1, 3}[target->orientation - 1];
    if (x == 0 && y > 0)
        return (uint8_t[]){1, 3, 5, 7}[target->orientation - 1];
    if (x < 0 && y == 0)
        return (uint8_t[]){7, 1, 3, 5}[target->orientation - 1];
    if (x > 0 && y == 0)
        return (uint8_t[]){3, 5, 7, 1}[target->orientation - 1];
    if (x > 0 && y > 0)
        return (uint8_t[]){2, 4, 6, 8}[target->orientation - 1];
    if (x > 0 && y < 0)
        return (uint8_t[]){4, 6, 8, 2}[target->orientation - 1];
    if (x < 0 && y > 0)
        return (uint8_t[]){8, 2, 4, 6}[target->orientation - 1];
    if (x < 0 && y < 0)
        return (uint8_t[]){6, 8, 2, 4}[target->orientation - 1];
    return 0;
}

static void notify_users(
    const zappy_server_t *server,
    const ai_t *ai,
    const char *message)
{
    ai_t *target;
    int broadcast_direction = 0;

    TAILQ_FOREACH(target, &server->ais, entries)
        if (target->fd != ai->fd) {
            broadcast_direction = get_broadcast_direction(ai, target);
            protocol_server_send(server->socket, target->fd, "message %i, %s",
                broadcast_direction, message);
        }
}

void broadcast_text(
    const zappy_server_t *server,
    ai_t *ai,
    const char *message)
{
    if (message[0] != ' ' || !message[1]) {
        protocol_server_send(server->socket, ai->fd, "ko");
        return;
    }
    notify_users(server, ai, message + 1);
    protocol_server_send(server->socket, ai->fd, "ok");
}
