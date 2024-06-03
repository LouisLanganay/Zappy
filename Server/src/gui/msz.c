/*
** EPITECH PROJECT, 2024
** Server
** File description:
** msz
*/

#include "server.h"

void msz(
    const zappy_server_t *server,
    const int interlocutor,
    UNUSED const char *message)
{
    protocol_server_send_message(server->socket, interlocutor, "msz %d %d\n",
        server->width, server->height);
}
