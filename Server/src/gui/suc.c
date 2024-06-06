/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** suc
*/

#include "server.h"

void suc(
    zappy_server_t *server,
    const int interlocutor)
{
    protocol_server_send(server->socket, interlocutor, "suc");
}
