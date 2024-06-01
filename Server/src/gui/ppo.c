/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ppo
*/

#include <string.h>

#include "server/gui.h"

void ppo(const zappy_server_t *server, const protocol_payload_t *payload)
{
    protocol_packet_t packet = { EVT_PPO, {0} };
    uint16_t id = 0;
    ai_pos_t ai_pos = {0};
    const ai_t *ai = NULL;

    memcpy(&id, &payload->packet.data, sizeof(uint16_t));
    ai = get_ai_by_id(server, id);
    if (ai == NULL) {
        sbp(server, payload);
        return;
    }
    ai_pos = (ai_pos_t){ ai->id, { ai->pos.x, ai->pos.y }, ai->orientation };
    memcpy(&packet.data, &ai_pos, sizeof(ai_pos_t));
}
