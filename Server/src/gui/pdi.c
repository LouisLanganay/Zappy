/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** pdi
*/

#include "server/gui.h"

void pdi(
    const zappy_server_t *server,
    const ai_t *ai)
{
    gui_send_to_all(server, "pdi %d", ai->id);
}
