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
#include <time.h>
#include <unistd.h>

#include "protocol/client.h"

static uint16_t parse_message(
    protocol_client_t *client,
    const int fd,
    char *buffer)
{
    protocol_payload_t *payload;
    uint16_t size = 0;

    for (; buffer[size] && buffer[size] != '\n'; size++);
    if (size == 0 || !buffer[size])
        return size;
    buffer[size] = '\0';
    payload = calloc(1, sizeof(protocol_payload_t));
    if (!payload) {
        fprintf(stderr, "\033[31m[Error]\033[0m %s\n", strerror(errno));
        return 0;
    }
    payload->fd = fd;
    strncpy(payload->message, buffer, size);
    TAILQ_INSERT_TAIL(&client->payloads, payload, entries);
    return size;
}

static void parse_messages(
    protocol_client_t *client,
    const int fd,
    const uint16_t read_size)
{
    uint16_t parsed;

    for (uint16_t size = 0;;) {
        parsed = parse_message(client, fd, client->buffer + size);
        if (size + parsed >= read_size) {
            strcpy(client->buffer, client->buffer + size);
            client->buffer[read_size - size] = '\0';
            break;
        }
        size += parsed + 1;
    }
}

static bool receive_messages(
    protocol_client_t *client,
    const int fd)
{
    const uint16_t strlen_buffer = strlen(client->buffer);
    ssize_t read_size = read(fd, client->buffer + strlen_buffer,
        DATA_SIZE - strlen_buffer);

    if (read_size < 0) {
        fprintf(stderr, "\033[31m[Error]\033[0m %s\n", strerror(errno));
        return false;
    }
    if (read_size == 0) {
        client->is_connected = false;
        return false;
    }
    read_size += strlen_buffer;
    client->buffer[read_size] = '\0';
    parse_messages(client, fd, read_size);
    return true;
}

static void handle_payload(
    protocol_client_t *client,
    const int fd)
{
    protocol_payload_t *tmp = NULL;

    if (receive_messages(client, fd))
        return;
    printf("\033[33m[INFO]\033[0m Disconnected from server\n");
    while (!TAILQ_EMPTY(&client->payloads)) {
        tmp = TAILQ_FIRST(&client->payloads);
        TAILQ_REMOVE(&client->payloads, tmp, entries);
        free(tmp);
    }
}

protocol_payload_t *protocol_client_listen(
    protocol_client_t *client)
{
    memcpy(&client->readfds, &client->master_read_fds, sizeof(fd_set));
    memcpy(&client->writefds, &client->master_write_fds, sizeof(fd_set));
    if (select(FD_SETSIZE, &client->readfds, &client->writefds, NULL,
        NULL) == -1) {
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
