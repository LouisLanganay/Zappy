/*
** EPITECH PROJECT, 2024
** Protocol
** File description:
** protocol/client/listen
*/


#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "protocol/client.h"

static protocol_payload_t *receive_packet(
    protocol_client_t *client,
    const int fd)
{
    protocol_payload_t *payload = calloc(1, sizeof(protocol_payload_t));
    ssize_t read_size;

    if (!payload) {
        fprintf(stderr, "\033[31m[Error]\033[0m %s\n", strerror(errno));
        return NULL;
    }
    read_size = read(fd, &payload->packet, sizeof(protocol_packet_t));
    if (read_size < 0) {
        fprintf(stderr, "\033[31m[Error]\033[0m %s\n", strerror(errno));
        free(payload);
        return NULL;
    }
    if (read_size == 0) {
        client->is_connected = false;
        free(payload);
        return NULL;
    }
    return payload;
}

static void *handle_payload(
    protocol_client_t *client,
    const int fd)
{
    protocol_payload_t *payload = receive_packet(client, fd);
    protocol_payload_t *tmp = NULL;

    if (payload) {
        payload->fd = fd;
        TAILQ_INSERT_TAIL(&client->payloads, payload, entries);
        return payload;
    }
    while (!TAILQ_EMPTY(&client->payloads)) {
        tmp = TAILQ_FIRST(&client->payloads);
        TAILQ_REMOVE(&client->payloads, tmp, entries);
        free(tmp);
    }
    return NULL;
}

protocol_payload_t *protocol_client_listen(
    protocol_client_t *client)
{
    struct timeval tv = {0, 0};

    memcpy(&client->readfds, &client->master_read_fds, sizeof(fd_set));
    memcpy(&client->writefds, &client->master_write_fds, sizeof(fd_set));
    if (select(FD_SETSIZE, &client->readfds, &client->writefds, NULL,
        &tv) == -1) {
        fprintf(stderr, "\033[31m[Error]\033[0m %s\n", strerror(errno));
        return NULL;
    }
    for (int fd = 0; fd <= FD_SETSIZE; fd++) {
        if (!FD_ISSET(fd, &client->readfds))
            continue;
        if (fd == client->sockfd)
            continue;
        handle_payload(client, fd);
    }
    return TAILQ_FIRST(&client->payloads);
}
