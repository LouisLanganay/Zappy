/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** sbp
*/

#include "server.h"

void sbp(const zappy_server_t *server, const protocol_payload_t *payload)
{
    protocol_server_send_packet_type(server->socket, payload->fd, EVT_SBP);
}
