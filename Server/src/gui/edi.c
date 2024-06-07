/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** edi
*/

#include "server/gui.h"

void edi(
    zappy_server_t *server,
    const int interlocutor,
    const int egg_id)
{
    const ai_t *ai = get_ai_by_id(server, interlocutor);

    if (!ai) {
        sbp(server, interlocutor);
        return;
    }
    protocol_server_send(server->socket, interlocutor,
        "edi %d\n", egg_id);
}
