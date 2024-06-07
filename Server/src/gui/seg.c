/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** seg
*/

#include "server/gui.h"

void seg(
    const zappy_server_t *server,
    const team_t *team)
{
    gui_send_to_all(server, "seg %s", team->name);
}
