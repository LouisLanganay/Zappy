/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** pie
*/

#include "server/gui.h"

void pie(
    zappy_server_t *server,
    const int interlocutor)
{
    const ai_t *ai = get_ai_by_id(server, interlocutor);

    if (!ai) {
        sbp(server, interlocutor);
        return;
    }
    for (ai_t *tmp = server->ais.tqh_first; tmp; tmp = tmp->entries.tqe_next)
        if (tmp->pos.x == ai->pos.x && tmp->pos.y == ai->pos.y
            && tmp->level == ai->level && tmp->id == ai->id)
            protocol_server_send(server->socket, interlocutor,
                "pie %d %d %d\n",
                ai->pos.x, ai->pos.y, ai->level);
}
