/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** sgt
*/

#include "server/gui.h"

#include <string.h>
#include <stdio.h>

void sgt(
    zappy_server_t *server,
    const int interlocutor,
    UNUSED const char *message)
{
    const ai_t *ai = get_ai_by_id(server, interlocutor);

    if (!ai) {
        sbp(server, interlocutor);
        return;
    }

    protocol_server_send(server->socket, interlocutor,
        "sgt %d\n", server->freq);
}
