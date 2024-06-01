/*
** EPITECH PROJECT, 2024
** Server
** File description:
** msz
*/

#include <string.h>

#include "server.h"

void msz(const zappy_server_t *server, const protocol_payload_t *payload)
{
    protocol_packet_t packet = { EVT_MSZ, {0} };
    const vector2_t size = { server->width, server->height };

    memcpy(&packet.data, &size, sizeof(vector2_t));
    protocol_server_send_packet(server->socket, payload->fd, &packet);
}
