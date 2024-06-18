/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** protocol
*/

#include <stdio.h>
#include <stdarg.h>

#include "server.h"

bool mock_protocol_server_send(
    UNUSED protocol_server_t *server,
    UNUSED const int client_fd,
    const char *format,
    ...)
{
    char message[DATA_SIZE] = {0};
    va_list args;

    va_start(args, format);
    vsnprintf(message, sizeof(message) - 2, format, args);
    va_end(args);
    printf("To client %i: %s\n", client_fd, message);
    fflush(stdout);
    return true;
}
