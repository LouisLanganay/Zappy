/*
** EPITECH PROJECT, 2024
** Protocol
** File description:
** protocol/client/close
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "protocol/client.h"

void protocol_client_close(protocol_client_t *client)
{
    if (close(client->network_data.sockfd) == -1)
        fprintf(stderr, "\033[31m[ERROR]\033[0m %s\n", strerror(errno));
    free(client);
}
