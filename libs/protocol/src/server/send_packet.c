/*
** EPITECH PROJECT, 2024
** Protocol
** File description:
** protocol/server/send_packet
*/

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>

#include "protocol/server.h"

static bool set_client_fd(
    protocol_server_t *server,
    const int client_fd)
{
    protocol_client_t *client;

    TAILQ_FOREACH(client, &server->clients, entries)
        if (client->network_data.sockfd == client_fd) {
            FD_SET(client->network_data.sockfd, &server->write_fds);
            return true;
        }
    fprintf(stderr, "\033[31m[ERROR]\033[0m client not found\n");
    return false;
}

bool protocol_server_send(
    protocol_server_t *server,
    const int client_fd,
    const char *format,
    ...)
{
    char message[DATA_SIZE + 1] = {0};
    va_list args;

    if (!set_client_fd(server, client_fd))
        return false;
    va_start(args, format);
    vsnprintf(message, sizeof(message) - 2, format, args);
    va_end(args);
    message[strlen(message)] = '\n';
    if (write(client_fd, message, strlen(message)) > 0)
        return true;
    fprintf(stderr, "\033[31m[ERROR]\033[0m %s\n", strerror(errno));
    return false;
}
