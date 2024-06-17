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
    const int nb_players,
    const ai_t *ai,
    const ai_t *ais[])
{
    char formatted_message[DATA_SIZE] = {0};

    snprintf(formatted_message, DATA_SIZE, "pic %d %d %d",
        ai->pos.x, ai->pos.y, ai->level);
    for (uint8_t i = 0; i < nb_players; i++)
        snprintf(formatted_message + strlen(formatted_message), DATA_SIZE,
            " %d", ais[i]->id);
    gui_send_to_all(server, formatted_message);
}
