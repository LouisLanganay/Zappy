/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** pfk
*/

#include "server/gui.h"

void pfk(
    const zappy_server_t *server,
    const int interlocutor)
{
    const ai_t *ai = get_ai_by_id(server, interlocutor);

    if (!ai) {
        sbp(server, interlocutor);
        return;
    }

    protocol_server_send_message(server->socket, interlocutor,
    "pfk %d\n", ai->id);
}