/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** smg
*/

#include "server.h"

void smg(
    zappy_server_t *server,
    const char *message)
{
    gui_send_to_all(server, "smg %s", message);
}
