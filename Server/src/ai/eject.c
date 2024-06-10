/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** eject
*/

#include <stdio.h>

#include "server/ai_header.h"

static void move_ai(
    const zappy_server_t *server,
    ai_t *t_ai,
    ai_t *ai)
{
    switch (ai->orientation) {
        case (NORTH):
            t_ai->pos.y = (t_ai->pos.y + server->height - 1) % server->height;
            protocol_server_send(server->socket, t_ai->fd, "eject: 6");
            break;
        case (EAST):
            t_ai->pos.x = (t_ai->pos.x + 1) % server->width;
            protocol_server_send(server->socket, t_ai->fd, "eject: 8");
            break;
        case (SOUTH):
            t_ai->pos.y = (t_ai->pos.y + 1) % server->height;
            protocol_server_send(server->socket, t_ai->fd, "eject: 2");
            break;
        case (WEST):
            t_ai->pos.x = (t_ai->pos.x + server->width - 1) % server->width;
            protocol_server_send(server->socket, t_ai->fd, "eject: 4");
            break;
    }
}

void eject(
    const zappy_server_t *server,
    ai_t *ai,
    UNUSED const char *message)
{
    bool ejected = false;
    ai_t *target_ai;

    TAILQ_FOREACH(target_ai, &server->ais, entries)
        if (target_ai->fd != ai->fd && (target_ai->pos.x == ai->pos.x &&
            target_ai->pos.y == ai->pos.y)) {
            move_ai(server, target_ai, ai);
            ejected = true;
        }
    if (!ejected)
        protocol_server_send(server->socket, ai->fd, "ko");
    else
        protocol_server_send(server->socket, ai->fd, "ok");
}
