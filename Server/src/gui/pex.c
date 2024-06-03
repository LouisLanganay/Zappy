/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** pex
*/

#include <stdio.h>

#include "server/gui.h"

void pex(
    const zappy_server_t *server,
    const int interlocutor)
{
    char formatted_message[DATA_SIZE];

    snprintf(formatted_message, DATA_SIZE, "pex %d\n", interlocutor);
    gui_send_to_all(server, formatted_message);
}
