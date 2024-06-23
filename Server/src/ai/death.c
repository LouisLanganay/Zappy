/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** death
*/

#include "server/gui.h"

void death(
    zappy_server_t *server,
    ai_t *ai)
{
    server_send(server, ai->fd, "dead");
    ai->state = DEAD;
    pdi(server, ai);
    verbose(server, "AI %d died", ai->id);
}
