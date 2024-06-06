/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ebo
*/

#include "server/gui.h"

void ebo(
    const zappy_server_t *server,
    const int interlocutor,
    const int egg_id)
{
    const ai_t *ai = get_ai_by_id(server, interlocutor);

    if (!ai) {
        sbp(server, interlocutor);
        return;
    }

    protocol_server_send_message(server->socket, interlocutor,
        "ebo %d\n", egg_id);
}
