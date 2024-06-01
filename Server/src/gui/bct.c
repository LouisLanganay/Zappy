/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** bct
*/

#include <string.h>

#include "server/gui.h"

void bct(const zappy_server_t *server, const protocol_payload_t *payload)
{
    protocol_packet_t packet = { EVT_BCT, {0} };
    tile_t tile = {0};

    memcpy(&tile.pos, &payload->packet.data, sizeof(vector2_t));
    if (tile.pos.x >= server->width || tile.pos.y >= server->height) {
        sbp(server, payload);
        return;
    }
    memcpy(&tile.inventory, &server->map[tile.pos.y][tile.pos.x],
        sizeof(inventory_t));
    memcpy(&packet.data, &tile, sizeof(tile_t));
    protocol_server_send_packet(server->socket, payload->fd, &packet);
}
