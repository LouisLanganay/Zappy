/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** mct
*/

#include <stdio.h>

#include "server/gui.h"

void mct(
    zappy_server_t *server,
    const int interlocutor,
    UNUSED const char *message)
{
    char formatted_message[DATA_SIZE];
    vector2_t pos;

    for (pos.y = 0; pos.y < server->height; pos.y++)
        for (pos.x = 0; pos.x < server->width; pos.x++) {
            snprintf(formatted_message, DATA_SIZE,
                " %d %d\n", pos.x, pos.y);
            bct(server, interlocutor, formatted_message);
        }
}
