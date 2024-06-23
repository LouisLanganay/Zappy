/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** plv
*/

#include <stdio.h>

#include "server/gui.h"

// Response to "plv #n\n"
void plv(
    zappy_server_t *server,
    const int interlocutor,
    const char *message)
{
    uint16_t id;
    ai_t *ai;

    if (sscanf(message, " %hd", &id) != 1) {
        sbp(server, interlocutor);
        return;
    }
    ai = ai_get_by_id(server, id);
    if (!ai) {
        sbp(server, interlocutor);
        return;
    }
    server_send(server, interlocutor, "plv %d %d",
        ai->id, ai->level);
}
