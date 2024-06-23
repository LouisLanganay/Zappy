/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** pfk
*/

#include "server/gui.h"

void pfk(
    zappy_server_t *server,
    const ai_t *ai)
{
    gui_send_to_all(server, "pfk %i", ai->id);
}
