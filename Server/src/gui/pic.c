/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** pic
*/

#include <string.h>
#include <stdio.h>

#include "server/gui.h"

void pic(
    const zappy_server_t *server,
    const ai_t **ais)
{
    char formatted_message[DATA_SIZE] = {0};

    snprintf(formatted_message, DATA_SIZE, "pic %d %d %d",
        ais[0]->pos.x, ais[0]->pos.y, ais[0]->level);
    for (uint8_t i = 0; ais[i]; i++)
        snprintf(formatted_message + strlen(formatted_message), DATA_SIZE,
            " %d", ais[i]->id);
    gui_send_to_all(server, formatted_message);
}
