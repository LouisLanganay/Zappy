/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** pbc
*/

#include "server.h"

void pbc(
    zappy_server_t *server,
    const ai_t *ai,
    const char *message)
{
    gui_send_to_all(server, "pbc %d %s", ai->id, message);
}
