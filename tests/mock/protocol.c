/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** protocol
*/

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "server.h"

bool mock_protocol_server_send(
    UNUSED protocol_server_t *server,
    const int client_fd,
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

protocol_server_t *mock_protocol_server_create(
    UNUSED const int port)
{
    protocol_server_t *server = calloc(1, sizeof(protocol_server_t));

    if (!server)
        return NULL;
    TAILQ_INIT(&server->clients);
    TAILQ_INIT(&server->payloads);
    TAILQ_INIT(&server->new_connections);
    TAILQ_INIT(&server->lost_connections);
    return server;
}
