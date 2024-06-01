/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** pex
*/

#include <string.h>

#include "server/gui.h"

void pex(const zappy_server_t *server, const ai_t *ai)
{
    protocol_packet_t packet = { EVT_PEX, {0} };

    memcpy(&packet.data, &ai->id, sizeof(uint16_t));
    gui_send_to_all(server, &packet);
}
