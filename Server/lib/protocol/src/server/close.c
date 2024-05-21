/*
** EPITECH PROJECT, 2024
** Protocol
** File description:
** protocol/server/close
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "protocol/server.h"

void protocol_server_close(
    protocol_server_t *server)
{
    for (protocol_client_t *client = TAILQ_FIRST(&server->clients); client;
        client = TAILQ_FIRST(&server->clients)) {
        TAILQ_REMOVE(&server->clients, client, entries);
        if (close(client->network_data.sockfd) == -1)
            fprintf(stderr, "\033[31m[ERROR]\033[0m %s\n", strerror(errno));
        free(client);
    }
    if (close(server->network_data.sockfd) == -1)
        fprintf(stderr, "\033[31m[ERROR]\033[0m %s\n", strerror(errno));
    free(server);
}
