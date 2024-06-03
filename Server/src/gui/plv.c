/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** plv
*/

#include "server/gui.h"

void plv(
    const zappy_server_t *server,
    const int interlocutor,
    UNUSED const char *message)
{
    const ai_t *ai = get_ai_by_id(server, interlocutor);

    if (!ai) {
        sbp(server, interlocutor);
        return;
    }
    protocol_server_send_message(server->socket, interlocutor, "plv %d %d\n",
        ai->id, ai->level);
}
