/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** pnw
*/

#include <string.h>

#include "server.h"

void pnw(const zappy_server_t *server, const ai_t *ai)
{
    protocol_packet_t packet = { EVT_PNW, {0} };
    const ai_info_t ai_info = { ai->id, { ai->pos.x, ai->pos.y },
        ai->orientation, ai->level, ai->team->name };

    memcpy(&packet.data, &ai_info, sizeof(ai_info));
    gui_send_to_all(server, &packet);
}
