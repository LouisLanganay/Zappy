/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ppo
*/

#include "server/gui.h"

void ppo(
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
        "ppo %d %d %d %d\n",
        ai->id, ai->pos.x, ai->pos.y, ai->orientation);
}
