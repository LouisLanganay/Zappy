/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** plv
*/

#include <string.h>

#include "server/gui.h"

void plv(const zappy_server_t *server, const protocol_payload_t *payload)
{
    protocol_packet_t packet = { EVT_PLV, {0} };
    uint16_t id = 0;
    ai_level_t ai_level = {0};
    const ai_t *ai;

    memcpy(&id, &payload->packet.data, sizeof(uint16_t));
    ai = get_ai_by_id(server, id);
    if (!ai) {
        sbp(server, payload);
        return;
    }
    ai_level = (ai_level_t){ ai->id, ai->level };
    memcpy(&packet.data, &ai_level, sizeof(ai_level_t));
}
