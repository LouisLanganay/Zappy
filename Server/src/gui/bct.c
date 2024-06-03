/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** bct
*/

#include <stdio.h>

#include "server/gui.h"

void bct(
    const zappy_server_t *server,
    const int interlocutor,
    const char *message)
{
    vector2_t pos;

    scanf(message, "%d %d", &pos.x, &pos.y);
    if (pos.x >= server->width || pos.y >= server->height) {
        sbp(server, interlocutor);
        return;
    }
    protocol_server_send_message(server->socket, interlocutor,
        "bct %d %d %d %d %d %d %d %d %d\n",
        pos.x, pos.y, server->map[pos.y][pos.x].food,
        server->map[pos.y][pos.x].linemate,
        server->map[pos.y][pos.x].deraumere, server->map[pos.y][pos.x].sibur,
        server->map[pos.y][pos.x].mendiane, server->map[pos.y][pos.x].phiras,
        server->map[pos.y][pos.x].thystame);
}
