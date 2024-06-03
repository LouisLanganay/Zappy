/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** suc
*/

#include "server.h"

void suc(
    const zappy_server_t *server,
    const int interlocutor)
{
    protocol_server_send_message(server->socket, interlocutor, "suc\n");
}
