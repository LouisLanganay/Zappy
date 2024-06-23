/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** bct
*/

#include <stdio.h>

#include "server/gui.h"

// Response to "bct X Y\n"
void bct(
    zappy_server_t *server,
    const int interlocutor,
    const char *message)
{
    vector2_t pos = {0};

    if (sscanf(message, " %hd %hd", &pos.x, &pos.y) != 2) {
        sbp(server, interlocutor);
        return;
    }
    if (pos.x >= server->width || pos.y >= server->height) {
        sbp(server, interlocutor);
        return;
    }
    server_send(server, interlocutor,
        "bct %d %d %d %d %d %d %d %d %d",
        pos.x, pos.y, server->map[pos.y][pos.x].food,
        server->map[pos.y][pos.x].linemate,
        server->map[pos.y][pos.x].deraumere, server->map[pos.y][pos.x].sibur,
        server->map[pos.y][pos.x].mendiane, server->map[pos.y][pos.x].phiras,
        server->map[pos.y][pos.x].thystame);
}
