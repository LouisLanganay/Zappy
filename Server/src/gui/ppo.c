/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ppo
*/

#include <stdio.h>

#include "server/gui.h"

// Response to "ppo #n X Y O\n"
void ppo(
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
    protocol_server_send(server->socket, interlocutor,
        "ppo %d %d %d %d",
        ai->id, ai->pos.x, ai->pos.y, ai->orientation);
}

void server_ppo(
    const zappy_server_t *server,
    const ai_t *ai)
{
    gui_t *gui;

    TAILQ_FOREACH(gui, &server->guis, entries)
        protocol_server_send(
            server->socket, gui->fd, "pnw %d %d %d %d %d %s", ai->id,
            ai->pos.x, ai->pos.y, ai->orientation, ai->level, ai->team->name);
}
