/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** pin
*/

#include <string.h>

#include "server/gui.h"

void pin(const zappy_server_t *server, const protocol_payload_t *payload)
{
    protocol_packet_t packet = { EVT_PIN, {0} };
    uint16_t id = 0;
    ai_inventory_t ai_inventory = {0};
    const ai_t *ai;

    memcpy(&id, &payload->packet.data, sizeof(uint16_t));
    ai = get_ai_by_id(server, id);
    if (!ai) {
        sbp(server, payload);
        return;
    }
    ai_inventory = (ai_inventory_t){ ai->id, ai->pos, ai->inventory };
    memcpy(&packet.data, &ai_inventory, sizeof(ai_inventory_t));
    protocol_server_send_packet(server->socket, payload->fd, &packet);
}
