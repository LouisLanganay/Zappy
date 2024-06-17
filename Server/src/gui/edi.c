/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** edi
*/

#include "server/gui.h"

void edi(
    const zappy_server_t *server,
    const uint16_t egg_id)
{
    gui_send_to_all(server, "edi %d", egg_id);
}
