/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** death
*/

#include "server/gui.h"

void death(
    const zappy_server_t *server,
    ai_t *ai)
{
    protocol_server_send(server->socket, ai->fd, "dead");
    ai->is_dead = true;
    pdi(server, ai);
}
