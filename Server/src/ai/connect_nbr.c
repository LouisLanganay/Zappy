/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** connect_nbr
*/

#include "server/ai_header.h"

void connect_nbr(
    zappy_server_t *server,
    ai_t *ai,
    UNUSED const char *message)
{
    server_send(server, ai->fd, "%d", ai->team->slots);
}
