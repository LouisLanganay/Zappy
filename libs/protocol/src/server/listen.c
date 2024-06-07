/*
** EPITECH PROJECT, 2024
** Protocol
** File description:
** protocol/server/listen
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "protocol/server.h"

static void add_new_connection(
    protocol_server_t *server,
    const int fd)
{
    protocol_connection_t *connection = calloc(1,
        sizeof(protocol_connection_t));

    if (!connection) {
        fprintf(stderr, "\033[31m[ERROR]\033[0m %s\n", strerror(errno));
        return;
    }
    connection->fd = fd;
    TAILQ_INSERT_TAIL(&server->new_connections, connection, entries);
}

static void add_lost_connection(
    protocol_server_t *server,
    const int fd)
{
    protocol_connection_t *connection = calloc(1,
        sizeof(protocol_connection_t));

    if (!connection) {
        fprintf(stderr, "\033[31m[ERROR]\033[0m %s\n", strerror(errno));
        return;
    }
    connection->fd = fd;
    TAILQ_INSERT_TAIL(&server->lost_connections, connection, entries);
}

static uint16_t parse_message(
    protocol_server_t *server,
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
    TAILQ_INSERT_TAIL(&server->payloads, payload, entries);
    return size;
}

static void parse_messages(
    protocol_server_t *server,
    protocol_client_t *client,
    const int fd,
    const uint16_t read_size)
{
    uint16_t parsed;

    for (uint16_t size = 0;;) {
        parsed = parse_message(server, fd, client->buffer + size);
        if (size + parsed >= read_size) {
            strcpy(client->buffer, client->buffer + size);
            client->buffer[read_size - size] = '\0';
            break;
        }
        size += parsed + 1;
    }
}

static bool receive_messages(
    protocol_server_t *server,
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
    parse_messages(server, client, fd, read_size);
    return true;
}

static void handle_payload(
    const int fd,
    protocol_server_t *server)
{
    protocol_client_t *client;

    TAILQ_FOREACH(client, &server->clients, entries)
        if (client->network_data.sockfd == fd)
            break;
    if (receive_messages(server, client, fd))
        return;
    FD_CLR(fd, &server->master_read_fds);
    FD_CLR(fd, &server->master_write_fds);
    TAILQ_REMOVE(&server->clients, client, entries);
    add_lost_connection(server, fd);
    free(client);
    close(fd);
}

static bool server_select(
    protocol_server_t *server)
{
    memcpy(&server->read_fds, &server->master_read_fds, sizeof(fd_set));
    memcpy(&server->write_fds, &server->master_write_fds, sizeof(fd_set));
    if (select(FD_SETSIZE, &server->read_fds, &server->write_fds,
        NULL, NULL) != -1)
        return true;
    if (errno != EINTR)
        fprintf(stderr, "\033[31m[ERROR]\033[0m %s\n", strerror(errno));
    return false;
}

static int accept_client(
    const protocol_server_t *server,
    protocol_client_t *client)
{
    socklen_t size;

    size = sizeof(struct sockaddr_in);
    return accept(
        server->network_data.sockfd,
        (struct sockaddr*)&client->network_data.server_addr,
        &size
    );
}

static bool new_client(
    protocol_server_t *server)
{
    protocol_client_t *client = calloc(1, sizeof(protocol_client_t));
    int socket;

    if (!client) {
        fprintf(stderr, "\033[31m[ERROR]\033[0m %s\n", strerror(errno));
        return false;
    }
    socket = accept_client(server, client);
    if (socket < 0) {
        fprintf(stderr, "\033[31m[ERROR]\033[0m %s\n", strerror(errno));
        free(client);
        return false;
    }
    client->network_data.sockfd = socket;
    TAILQ_INSERT_TAIL(&server->clients, client, entries);
    FD_SET(socket, &server->master_read_fds);
    FD_SET(socket, &server->master_write_fds);
    add_new_connection(server, socket);
    return true;
}

protocol_payload_t *protocol_server_listen(
    protocol_server_t *server)
{
    TAILQ_INIT(&server->payloads);
    if (!server_select(server))
        return NULL;
    for (int fd = 0; fd < FD_SETSIZE; fd++) {
        if (!FD_ISSET(fd, &server->read_fds))
            continue;
        if (fd == server->network_data.sockfd)
            new_client(server);
        else
            handle_payload(fd, server);
    }
    return TAILQ_FIRST(&server->payloads);
}
