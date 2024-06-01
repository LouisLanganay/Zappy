/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** pbc
*/

#include <string.h>

#include "server.h"

void pbc(const zappy_server_t *server, const ai_t *ai, const char *msg)
{
    protocol_packet_t packet = { EVT_PBC, {0} };
    broadcast_t broadcast = { ai->id, "" };

    memcpy(&broadcast.msg, msg, strlen(msg));
    memcpy(&packet.data, &broadcast, sizeof(broadcast_t));
    gui_send_to_all(server, &packet);
}
