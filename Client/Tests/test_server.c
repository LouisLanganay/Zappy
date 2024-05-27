/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** test_server
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "test_server.h"
#include <string.h>

test_server_t *test_server_create(int port) {
    test_server_t *test_server = malloc(sizeof(test_server_t));
    if (!test_server) {
        perror("Failed to allocate memory for test server");
        return NULL;
    }

    test_server->server = protocol_server_create(port);
    if (!test_server->server) {
        free(test_server);
        return NULL;
    }

    return test_server;
}

void test_server_run(test_server_t *test_server) {
    if (!test_server || !test_server->server)
        return;

    printf("Server is running...\n");
    int a = 0;

    while (protocol_server_is_open()) {
        protocol_payload_t *payload = protocol_server_listen(test_server->server);
        if (payload) {
            printf("Received packet: %s - Type: %i\n", payload->packet.data, payload->packet.type);
            if (a == 0) {
                protocol_packet_t packet = {1, "msz 10 10\n"};
                printf("Sending packet: %s\n", packet.data);
                int r = protocol_server_send_packet(&packet, payload->fd, test_server->server);
                printf("Result: %i\n", r);
                a++;
            }
        }
    }
}

void test_server_destroy(test_server_t *test_server) {
    if (test_server) {
        protocol_server_close(test_server->server);
        free(test_server);
    }
}
