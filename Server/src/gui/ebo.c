/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ebo
*/

#include "server/gui.h"

void ebo(
    zappy_server_t *server,
    const uint16_t egg_id)
{
    gui_send_to_all(server, "ebo %d", egg_id);
}
