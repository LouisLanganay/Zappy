/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** pdr
*/

#include "server/gui.h"

void pdr(
    zappy_server_t *server,
    const ai_t *ai,
    const uint8_t resource)
{
    gui_send_to_all(server, "pdr %i %i", ai->id, resource);
}
