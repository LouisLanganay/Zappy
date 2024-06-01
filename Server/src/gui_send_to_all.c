/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** gui_send_to_all
*/

#include <string.h>

#include "server.h"

void gui_send_to_all(const zappy_server_t *server, const protocol_packet_t *packet)
{
    const gui_t *gui = NULL;

    TAILQ_FOREACH(gui, &server->guis, entries)
        protocol_server_send_packet(server->socket, gui->fd, packet);
}
