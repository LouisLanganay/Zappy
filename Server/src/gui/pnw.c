/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** pnw
*/

#include "server.h"

void pnw(
    zappy_server_t *server,
    const ai_t *ai)
{
    gui_send_to_all(server, "pnw %d %d %d %d %d %s",
        ai->id, ai->pos.x, ai->pos.y, ai->orientation, ai->level,
        ai->team->name);
}
