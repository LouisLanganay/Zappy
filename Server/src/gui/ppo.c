/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ppo
*/

#include <stdio.h>

#include "server/gui.h"

void ppo(
    zappy_server_t *server,
    const int interlocutor,
    const char *message)
{
    uint16_t id;
    ai_t *ai;

    if (sscanf(message, " %hd", &id) != 1) {
        sbp(server, interlocutor);
        return;
    }
    ai = get_ai_by_id(server, id);
    if (!ai) {
        sbp(server, interlocutor);
        return;
    }
    protocol_server_send(server->socket, interlocutor,
        "ppo %d %d %d %d",
        ai->id, ai->pos.x, ai->pos.y, ai->orientation);
}
