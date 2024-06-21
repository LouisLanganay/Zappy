/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** map_handling
*/

#include "server/game.h"
#include <stdlib.h>

void trigger_meteor(
    const zappy_server_t *server)
{
    const float densities[] = {0.5, 0.3, 0.15, 0.1, 0.1, 0.08, 0.05};
    const uint32_t size = server->width * server->height;
    size_t quantities;

    for (size_t i = 0; i < sizeof(densities) / sizeof(densities[0]); ++i) {
        quantities = size * densities[i];
        if (quantities == 0)
            quantities = 1;
        for (size_t count = 0; count < quantities; ++count)
            server->map[rand() % server->width][rand() % server->width].resources[i] += 1;
    }
}
