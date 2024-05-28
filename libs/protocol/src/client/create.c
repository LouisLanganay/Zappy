/*
** EPITECH PROJECT, 2024
** Protocol
** File description:
** protocol/client/create
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#include "protocol/client.h"

bool protocol_client_is_connected(
    const protocol_client_t *client)
{
    return client->is_connected;
}

static protocol_client_t *client_socket(
    const char *ip, const int port)
{
    protocol_client_t *client = calloc(1, sizeof(protocol_client_t));

    if (!client) {
        fprintf(stderr, "\033[31m[Error]\033[0m %s\n", strerror(errno));
        return NULL;
    }
    client->network_data = (protocol_network_data_t){
        .sockfd = socket(AF_INET, SOCK_STREAM, 0),
        .server_addr = (struct sockaddr_in){
            .sin_addr.s_addr = inet_addr(ip),
            .sin_family = AF_INET,
            .sin_port = htons(port)
        }
    };
    if (client->network_data.sockfd > 0)
        return client;
    fprintf(stderr, "\033[31m[Error]\033[0m %s\n", strerror(errno));
    free(client);
    return NULL;
}

static bool client_connect(protocol_client_t *client)
{
    if (connect(
        client->network_data.sockfd,
        (struct sockaddr*)&client->network_data.server_addr,
        sizeof(struct sockaddr_in)
    ) >= 0)
        return true;
    fprintf(stderr, "\033[31m[Error]\033[0m %s\n", strerror(errno));
    free(client);
    return false;
}

protocol_client_t *protocol_client_create(const char *ip, const int port)
{
    protocol_client_t *client = client_socket(ip, port);

    if (!client || !client_connect(client))
        return NULL;
    client->is_connected = true;
    FD_ZERO(&client->master_read_fds);
    FD_ZERO(&client->master_write_fds);
    FD_SET(client->network_data.sockfd, &client->master_read_fds);
    FD_SET(client->network_data.sockfd, &client->master_write_fds);
    TAILQ_INIT(&client->payloads);
    return client;
}
