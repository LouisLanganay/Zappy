/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** suc
*/

#include "server.h"

void suc(
    const zappy_server_t *server)
{
    gui_send_to_all(server, "suc");
}
