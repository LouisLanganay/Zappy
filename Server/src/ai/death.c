/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** death
*/

#include <stdio.h>

#include "server/ai_header.h"
#include "server/gui.h"

void death(
    zappy_server_t *server,
    ai_t *ai,
    UNUSED const char *message)
{
    protocol_server_send(server->socket, ai->fd, "dead");
    pdi(server, ai);
}
