/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** inventory
*/

#include "server/ai_header.h"

void inventory(
    zappy_server_t *server,
    ai_t *ai,
    UNUSED const char *message)
{
    server_send(server, ai->fd, "[food %i, sibur %i, "
        "linemate %i, deraumere %i, mendiane %i, phiras %i, thystame %i]",
        ai->inventory.food, ai->inventory.sibur, ai->inventory.linemate,
        ai->inventory.deraumere, ai->inventory.mendiane, ai->inventory.phiras,
        ai->inventory.thystame);
}
