/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** add_deraumere
*/

#include "server/game.h"

void add_deraumere(
    zappy_server_t *server,
    uint16_t x,
    uint16_t y)
{
    server->map[y][x].deraumere++;
}
