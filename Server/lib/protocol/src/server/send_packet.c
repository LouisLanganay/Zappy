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

#include "protocol/server.h"

bool protocol_server_send_packet(
    const protocol_packet_t *packet,
    const int client_fd,
    protocol_server_t *server)
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
    const uint16_t type,
    const int client_fd,
    protocol_server_t *server)
{
    const protocol_packet_t packet = {type, {0}};

    return protocol_server_send_packet(&packet, client_fd, server);
}
