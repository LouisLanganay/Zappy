/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** add_mendiane
*/

#include "server/game.h"

void add_mendiane(
    zappy_server_t *server,
    uint16_t x,
    uint16_t y)
{
    server->map[y][x].mendiane++;
}
