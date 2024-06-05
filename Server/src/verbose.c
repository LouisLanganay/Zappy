/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** verbose
*/

#include <stdio.h>
#include <stdarg.h>

#include "server.h"

void verbose(
    const zappy_server_t *server,
    const char *format,
    ...)
{
    va_list args;

    if (!server->verbose)
        return;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}
