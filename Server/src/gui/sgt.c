/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** sgt
*/

#include "server/gui.h"

// Response to "sgt\n"
void sgt(
    zappy_server_t *server,
    const int interlocutor,
    UNUSED const char *message)
{
    server_send(server, interlocutor,
        "sgt %d", server->freq);
}
