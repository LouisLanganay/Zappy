/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** pgt
*/

#include "server/gui.h"

void pgt(
    const zappy_server_t *server,
    const ai_t *ai,
    const uint8_t resource)
{
    gui_send_to_all(server, "pgt %i %i", ai->id, resource);
}
