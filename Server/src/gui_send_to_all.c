/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** gui_send_to_all
*/

#include <stdio.h>
#include <stdarg.h>

#include "server.h"

void gui_send_to_all(
    const zappy_server_t *server,
    const char *message,
    ...)
{
    char formatted_message[DATA_SIZE] = {0};
    const gui_t *gui;
    va_list args;

    va_start(args, message);
    vsnprintf(formatted_message, DATA_SIZE, message, args);
    va_end(args);
    TAILQ_FOREACH(gui, &server->guis, entries)
        protocol_server_send(server->socket, gui->fd, message);
}
