/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** map
*/

#include <stdlib.h>
#include <string.h>

#include "server/game.h"
#include "server/gui.h"

bool init_map(
    zappy_server_t *server)
{
    const float densities[] = {0.5, 0.3, 0.15, 0.1, 0.1, 0.08, 0.05};

    for (uint8_t i = 0; i < sizeof(densities) / sizeof(densities[0]); ++i)
        server->base_ressources.resources[i]
            = server->width * server->height * densities[i];
    server->meteor_time = 1;
    server->map = calloc(server->height, sizeof(inventory_t *));
    if (!server->map)
        return false;
    for (uint16_t y = 0; y < server->height; ++y) {
        server->map[y] = calloc(server->width, sizeof(inventory_t));
        if (!server->map[y])
            return false;
        memset(server->map[y], 0, server->width * sizeof(inventory_t));
    }
    update_map(server);
    return true;
}

void update_map(
    zappy_server_t *server)
{
    gui_t *gui;

    server->meteor_time--;
    if (server->meteor_time > 0)
        return;
    server->meteor_time = 20;
    for (uint8_t i = 0; i < sizeof(server->ressources)
        / sizeof(server->ressources.resources[0]); ++i)
        while (server->ressources.resources[i]
            < server->base_ressources.resources[i]) {
            server->ressources.resources[i]++;
            server->map[rand() % server->width][rand() % server->height]
                .resources[i]++;
        }
    TAILQ_FOREACH(gui, &server->guis, entries)
        mct(server, gui->fd, "");
    verbose(server, "Meteor shower\n");
}
