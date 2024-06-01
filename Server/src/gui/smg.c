/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** smg
*/

#include <string.h>

#include "server.h"

void smg(const zappy_server_t *server, const char *msg)
{
    protocol_packet_t packet = { EVT_SMG, {0} };

    memcpy(&packet.data, msg, strlen(msg));
    gui_send_to_all(server, &packet);
}
