/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** pin
*/

#include <stdio.h>

#include "server/gui.h"

void pin(
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
        "pin %d %d %d %d %d %d %d %d %d %d",
        ai->id, ai->pos.x, ai->pos.y, ai->inventory.food,
        ai->inventory.linemate, ai->inventory.deraumere,
        ai->inventory.sibur, ai->inventory.mendiane,
        ai->inventory.phiras, ai->inventory.thystame);
}
