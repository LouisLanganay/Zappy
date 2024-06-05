/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** sgt
*/

#include "server.h"

void sgt(
    zappy_server_t *server,
    const int interlocutor,
    UNUSED const char *message)
{
    protocol_server_send_message(server->socket, interlocutor, "sgt %d\n",
        server->freq);
}
