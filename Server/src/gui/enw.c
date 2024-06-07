/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** enw
*/

#include "server/gui.h"

void enw(
    const zappy_server_t *server,
    const ai_t *ai,
    const int egg_id)
{
    gui_send_to_all(server, "enw %d %d %d %d",
        egg_id, ai->id, ai->pos.x, ai->pos.y);
}
