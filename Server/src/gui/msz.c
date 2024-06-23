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
    server_send(server, interlocutor, "msz %d %d",
        server->width, server->height);
}
