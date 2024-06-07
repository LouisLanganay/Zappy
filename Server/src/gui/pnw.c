/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** pnw
*/

#include <stdio.h>

#include "server.h"

void pnw(
    zappy_server_t *server,
    const ai_t *ai)
{
    char formatted_message[DATA_SIZE];

    snprintf(formatted_message, DATA_SIZE, "pnw %d %d %d %d %d %s\n",
        ai->id, ai->pos.x, ai->pos.y, ai->orientation, ai->level,
        ai->team->name);
    gui_send_to_all(server, formatted_message);
}
