/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** seg
*/

#include "server/gui.h"

void seg(
    const zappy_server_t *server,
    int interlocutor,
    const char *team_name)
{
    const ai_t *ai = get_ai_by_id(server, interlocutor);

    if (!ai) {
        sbp(server, interlocutor);
        return;
    }

    protocol_server_send_message(server->socket, interlocutor,
        "seg %s\n", team_name);
}