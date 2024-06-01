/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** tna
*/

#include <string.h>

#include "server.h"

void tna(const zappy_server_t *server, const protocol_payload_t *payload)
{
    protocol_packet_t packet = { EVT_TNA, {0} };
    const team_t *team;

    TAILQ_FOREACH(team, &server->teams, entries) {
        memset(&packet.data, 0, DATA_SIZE);
        memcpy(&packet.data, team->name, strlen(team->name));
        protocol_server_send_packet(server->socket, payload->fd, &packet);
    }
}
