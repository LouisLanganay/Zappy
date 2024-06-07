/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** smg
*/

#include <stdio.h>

#include "server.h"

void smg(
    zappy_server_t *server,
    const char *message)
{
    char formatted_message[DATA_SIZE];

    snprintf(formatted_message, DATA_SIZE, "smg %s\n", message);
    gui_send_to_all(server, formatted_message);
}
