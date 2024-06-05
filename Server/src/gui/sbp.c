/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** sbp
*/

#include "server.h"

void sbp(
    zappy_server_t *server,
    const int interlocutor)
{
    protocol_server_send_message(server->socket, interlocutor, "sbp\n");
}
