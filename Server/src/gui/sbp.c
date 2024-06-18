/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** sbp
*/

#include "server.h"

void sbp(
    const zappy_server_t *server)
{
    gui_send_to_all(server, "sbp");
}
