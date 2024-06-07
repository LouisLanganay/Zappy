/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** inventory
*/

#include <stdio.h>

#include "server/ai_header.h"

void inventory(
    const zappy_server_t *server,
    ai_t *ai,
    UNUSED const char *message)
{
    protocol_server_send(server->socket, ai->fd, "[food %i, sibur %i, "
    "linemate %i, deraumere %i, mendiane %i, phiras %i, thystame %i]\n",
    ai->inventory.food,
    ai->inventory.sibur,
    ai->inventory.linemate,
    ai->inventory.deraumere,
    ai->inventory.mendiane,
    ai->inventory.phiras,
    ai->inventory.thystame);
}
