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

bool protocol_server_send_packet(
    protocol_server_t *server,
    const int client_fd,
    const protocol_packet_t *packet)
{
    protocol_client_t *client;

    TAILQ_FOREACH(client, &server->clients, entries)
        if (client->network_data.sockfd == client_fd) {
            FD_SET(client->network_data.sockfd, &server->write_fds);
            break;
        }
    if (!client) {
        fprintf(stderr, "\033[31m[ERROR]\033[0m client not found\n");
        return false;
    }
    if (write(client_fd, packet, sizeof(protocol_packet_t)) == -1) {
        fprintf(stderr, "\033[31m[ERROR]\033[0m %s\n", strerror(errno));
        return false;
    }
    return true;
}

bool protocol_server_send_packet_type(
    protocol_server_t *server,
    const int client_fd,
    const uint16_t type)
{
    const protocol_packet_t packet = {type, {0}};

    return protocol_server_send_packet(server, client_fd, &packet);
}

bool protocol_server_send_message(
    protocol_server_t *server,
    const int client_fd,
    const char *format,
    ...)
{
    protocol_client_t *client;
    char message[DATA_SIZE];
    va_list args;

    TAILQ_FOREACH(client, &server->clients, entries)
        if (client->network_data.sockfd == client_fd) {
            FD_SET(client->network_data.sockfd, &server->write_fds);
            break;
        }
    if (!client) {
        fprintf(stderr, "\033[31m[ERROR]\033[0m client not found\n");
        return false;
    }
    va_start(args, format);
    vsnprintf(message, sizeof(message), format, args);
    va_end(args);
    if (write(client_fd, message, strlen(message)) > 0)
        return true;
    fprintf(stderr, "\033[31m[ERROR]\033[0m %s\n", strerror(errno));
    return false;
}
