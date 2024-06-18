/*
** EPITECH PROJECT, 2024
** Protocol
** File description:
** protocol/server/create
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#include "protocol/server.h"

static bool open_state(
    const bool new_state,
    const bool set)
{
    static bool state = false;

    if (set)
        state = new_state;
    return state;
}

static void server_stop(
    const int sig)
{
    if (sig != SIGINT)
        return;
    if (write(1, "\r", 1) == -1)
        fprintf(stderr, "\033[31m[Error]\033[0m %s\n", strerror(errno));
    open_state(false, true);
}

bool protocol_server_is_open(void)
{
    return open_state(false, false);
}

static protocol_server_t *create_socket(
    const int port)
{
    protocol_server_t *server = calloc(1, sizeof(protocol_server_t));

    if (!server) {
        fprintf(stderr, "\033[31m[Error]\033[0m %s\n", strerror(errno));
        return NULL;
    }
    server->network_data.sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (server->network_data.sockfd <= 0) {
        fprintf(stderr, "\033[31m[Error]\033[0m %s\n", strerror(errno));
        free(server);
        return NULL;
    }
    server->network_data.server_addr = (struct sockaddr_in){
        AF_INET, htons(port), {INADDR_ANY}, {0}
    };
    FD_ZERO(&server->master_read_fds);
    FD_ZERO(&server->master_write_fds);
    FD_SET(server->network_data.sockfd, &server->master_read_fds);
    FD_SET(server->network_data.sockfd, &server->master_write_fds);
    return server;
}

static bool server_setsockopt(
    protocol_server_t *server)
{
    if (setsockopt(server->network_data.sockfd, SOL_SOCKET, SO_REUSEADDR,
        &(int){1}, sizeof(int)) != -1)
        return true;
    fprintf(stderr, "\033[31m[Error]\033[0m %s\n", strerror(errno));
    close(server->network_data.sockfd);
    free(server);
    return false;
}

static bool server_bind(
    protocol_server_t *server)
{
    if (bind(server->network_data.sockfd,
        (const struct sockaddr *)&server->network_data.server_addr,
        sizeof(struct sockaddr_in)) != -1)
        return true;
    fprintf(stderr, "\033[31m[Error]\033[0m %s\n", strerror(errno));
    close(server->network_data.sockfd);
    free(server);
    return false;
}

static bool server_listen(protocol_server_t *server)
{
    if (listen(server->network_data.sockfd, SOMAXCONN) != -1)
        return true;
    fprintf(stderr, "\033[31m[Error]\033[0m %s\n", strerror(errno));
    close(server->network_data.sockfd);
    free(server);
    return false;
}

protocol_server_t *protocol_server_create(
    const int port)
{
    protocol_server_t *server = create_socket(port);
    struct sigaction sig = {0};

    if (!server || !server_setsockopt(server) || !server_bind(server))
        return NULL;
    TAILQ_INIT(&server->clients);
    TAILQ_INIT(&server->payloads);
    TAILQ_INIT(&server->new_connections);
    TAILQ_INIT(&server->lost_connections);
    if (!server_listen(server))
        return NULL;
    signal(SIGPIPE, SIG_IGN);
    sig.sa_handler = server_stop;
    sigaction(SIGINT, &sig, NULL);
    open_state(true, true);
    return server;
}
