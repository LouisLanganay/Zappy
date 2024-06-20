/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** notify
*/

#include <stdio.h>
#include <stdlib.h>

#include "server/ai_header.h"
#include "server/gui.h"


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
