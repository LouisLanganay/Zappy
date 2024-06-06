/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** sst
*/

#include "server/gui.h"

#include <string.h>
#include <stdio.h>

void sst(
    const zappy_server_t *server,
    const int interlocutor,
    const char *message)
{
    const ai_t *ai = get_ai_by_id(server, interlocutor);
    char msg[4];
    int time;

    scanf(message, "%s %d", msg, &time);
    if (!ai || time < 0 || strcmp(msg, "sst") != 0) {
        sbp(server, interlocutor);
        return;
    }

    protocol_server_send_message(server->socket, interlocutor, "sst %d\n", time);
}
