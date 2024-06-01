/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** suc
*/

#include "server.h"

void suc(const zappy_server_t *server, const protocol_payload_t *payload)
{
    protocol_server_send_packet_type(server->socket, payload->fd, EVT_SUC);
}
