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

bool protocol_client_send_packet(
    const protocol_client_t *client,
    const uint16_t type,
    const void *data,
    const int size)
{
    protocol_packet_t packet = {type, {0}};

    if (FD_ISSET(client->network_data.sockfd,
        &client->master_write_fds) == 0) {
        fprintf(stderr, "\033[31m[ERROR]\033[0m %s\n", strerror(errno));
        return false;
    }
    memcpy(packet.data, data, size);
    if (write(client->network_data.sockfd, &packet,
        sizeof(protocol_packet_t)) == -1) {
        fprintf(stderr, "\033[31m[ERROR]\033[0m %s\n", strerror(errno));
        return false;
    }
    return true;
}

bool protocol_client_send_message(
    const protocol_client_t *client,
    const char *format,
    ...)
{
    char message[DATA_SIZE];
    va_list args;

    if (FD_ISSET(client->network_data.sockfd,
        &client->master_write_fds) == 0) {
        fprintf(stderr, "\033[31m[ERROR]\033[0m %s\n", strerror(errno));
        return false;
    }
    va_start(args, format);
    vsnprintf(message, sizeof(message), format, args);
    va_end(args);
    if (write(client->network_data.sockfd, message, strlen(message)) == -1) {
        fprintf(stderr, "\033[31m[ERROR]\033[0m %s\n", strerror(errno));
        return false;
    }
    return true;
}
