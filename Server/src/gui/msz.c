/*
** EPITECH PROJECT, 2024
** Server
** File description:
** msz
*/

#include "server.h"

// Response to "msz\n"
void msz(
    zappy_server_t *server,
    const int interlocutor,
    UNUSED const char *message)
{
    protocol_server_send(server->socket, interlocutor, "msz %d %d",
        server->width, server->height);
}
