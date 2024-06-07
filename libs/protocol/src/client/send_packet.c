/*
** EPITECH PROJECT, 2024
** Protocol
** File description:
** protocol/client/send_packet
*/

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>

#include "protocol/client.h"

bool protocol_client_send(
    const protocol_client_t *client,
    const char *format,
    ...)
{
    char message[DATA_SIZE + 1] = {0};
    va_list args;

    if (FD_ISSET(client->network_data.sockfd,
        &client->master_write_fds) == 0) {
        fprintf(stderr, "\033[31m[ERROR]\033[0m %s\n", strerror(errno));
        return false;
    }
    va_start(args, format);
    vsnprintf(message, sizeof(message) - 2, format, args);
    va_end(args);
    message[strlen(message)] = '\n';
    if (write(client->network_data.sockfd, message, strlen(message)) < 0) {
        fprintf(stderr, "\033[31m[ERROR]\033[0m %s\n", strerror(errno));
        return false;
    }
    return true;
}
