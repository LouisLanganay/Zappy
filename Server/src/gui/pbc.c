/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** pbc
*/

#include <stdio.h>

#include "server.h"

void pbc(
    const zappy_server_t *server,
    const ai_t *ai,
    const char *message)
{
    char formatted_message[DATA_SIZE];

    snprintf(formatted_message, DATA_SIZE, "pbc %d %s\n", ai->id, message);
    gui_send_to_all(server, formatted_message);
}
