/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** map_handling
*/

#include "server/game.h"
#include <stdlib.h>
#include <time.h>

void fill_map(
    const size_t num_resources,
    size_t quantities[num_resources],
    uint16_t *resources[],
    zappy_server_t *server)
{
    uint16_t x = 0;
    uint16_t y = 0;

    for (size_t i = 0; i < num_resources; ++i) {
        if (quantities[i] == 0) {
            quantities[i] = 1;
        }
    }
    for (size_t res_index = 0; res_index < num_resources; ++res_index) {
        for (size_t count = 0; count < quantities[res_index]; ++count) {
            x = rand() % server->width;
            y = rand() % server->height;
            resources[res_index][y * server->width + x]++;
        }
    }
}

void trigger_meteor(zappy_server_t *server)
{
    const double densities[] = {0.5, 0.3, 0.15, 0.1, 0.1, 0.08, 0.05};
    const size_t num_resources = sizeof(densities) / sizeof(densities[0]);
    uint16_t *resources[] = {
        &server->map[0][0].food,
        &server->map[0][0].linemate,
        &server->map[0][0].deraumere,
        &server->map[0][0].sibur,
        &server->map[0][0].mendiane,
        &server->map[0][0].phiras,
        &server->map[0][0].thystame
    };
    size_t quantities[num_resources];
    size_t map_area = server->width * server->height;

    for (size_t i = 0; i < num_resources; ++i)
        quantities[i] = (size_t)(map_area * densities[i]);
    fill_map(num_resources, quantities, resources, server);
}
