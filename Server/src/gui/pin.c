/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** pin
*/

#include "server/gui.h"

void pin(
    const zappy_server_t *server,
    const int interlocutor,
    UNUSED const char *message)
{
    const ai_t *ai = get_ai_by_id(server, interlocutor);

    if (!ai) {
        sbp(server, interlocutor);
        return;
    }
    protocol_server_send_message(server->socket, interlocutor,
        "pin %d %d %d %d %d %d %d %d %d %d\n",
        ai->id, ai->pos.x, ai->pos.y, ai->inventory.food,
        ai->inventory.linemate, ai->inventory.deraumere,
        ai->inventory.sibur, ai->inventory.mendiane,
        ai->inventory.phiras, ai->inventory.thystame);
}
