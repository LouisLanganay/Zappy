/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** connect_nbr
*/

#include "server/ai_header.h"

void connect_nbr(
    zappy_server_t *server,
    UNUSED ai_t *ai,
    UNUSED const char *message)
{
    protocol_server_send(server->socket, ai->fd, "%d", team_get_empty_slots(
        server, ai->team));
}
