/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** pex
*/

#include "server/gui.h"

void pex(
    zappy_server_t *server,
    const ai_t *ai)
{
    gui_send_to_all(server, "pex %d", ai->id);
}
