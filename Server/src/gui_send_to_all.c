/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** gui_send_to_all
*/

#include "server.h"

void gui_send_to_all(
    const zappy_server_t *server,
    const char *message)
{
    const gui_t *gui;

    TAILQ_FOREACH(gui, &server->guis, entries)
        protocol_server_send_message(server->socket, gui->fd, message);
}
