/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** pie
*/

#include "server/gui.h"

void pie(
    const zappy_server_t *server,
    const ai_t *ai)
{
    gui_send_to_all(server, "pie %d %d %d",
        ai->pos.x, ai->pos.y, ai->orientation);
}
