/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** add_linemate
*/

#include "server/game.h"

void add_linemate(
    zappy_server_t *server,
    uint16_t x,
    uint16_t y)
{
    server->map[y][x].linemate++;
}
