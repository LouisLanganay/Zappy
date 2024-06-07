/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** pic
*/

#include "server/gui.h"

void pic(
    zappy_server_t *server,
    const int interlocutor)
{
    const ai_t *ai = get_ai_by_id(server, interlocutor);

    if (!ai) {
        sbp(server, interlocutor);
        return;
    }
    protocol_server_send(server->socket, interlocutor,
        "pic %d %d %d",
        ai->pos.x, ai->pos.y, ai->level);
    for (ai_t *tmp = server->ais.tqh_first; tmp; tmp = tmp->entries.tqe_next)
        if (tmp->pos.x == ai->pos.x && tmp->pos.y == ai->pos.y
            && tmp->level == ai->level && tmp->id != ai->id)
            protocol_server_send(server->socket, interlocutor,
                " %d", tmp->id);
    protocol_server_send(server->socket, interlocutor, "\n");
}
