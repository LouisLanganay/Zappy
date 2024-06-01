/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** mct
*/

#include <string.h>

#include "server/gui.h"

void mct(const zappy_server_t *server, const protocol_payload_t *payload)
{
    protocol_payload_t _payload = { .fd = 0, .packet = {0} };
    vector2_t pos = {0};

    for (pos.y = 0; pos.y < server->height; pos.y++)
        for (pos.x = 0; pos.x < server->width; pos.x++) {
            memcpy(&_payload.packet.data, &pos, sizeof(vector2_t));
            bct(server, payload);
        }
}
