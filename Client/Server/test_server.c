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
#include "../Source/API/Events.h"

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
            printf("Received packet: %s\n", payload->message);
            if (a == 0) {
                printf("Sending message: msz 10 10\n");
                int r = protocol_server_send(test_server->server, payload->fd, "msz 10 10\n");
                printf("Result: %i\n", r);
                a++;
                sleep(0.5);
                printf("Sending message: tna team1\n");
                r = protocol_server_send(test_server->server, payload->fd, "tna team1\n");
                printf("Result: %i\n", r);
                sleep(0.5);
                printf("Sending message: tna team2\n");
                r = protocol_server_send(test_server->server, payload->fd, "tna team2\n");
                printf("Result: %i\n", r);
                sleep(0.5);
                printf("Sending message: pnw 1 2 2 1 1 team1\n");
                r = protocol_server_send(test_server->server, payload->fd, "pnw 1 2 2 1 1 team1\n");
                printf("Result: %i\n", r);
                sleep(0.5);
                printf("Sending message: pnw 2 3 3 4 1 team2\n");
                r = protocol_server_send(test_server->server, payload->fd, "pnw 2 3 3 4 1 team2\n");
                printf("Result: %i\n", r);
                sleep(0.5);
                printf("Sending message: pin 1 2 2 5 5 5 5 5 5 5\n");
                r = protocol_server_send(test_server->server, payload->fd, "pin 1 2 2 5 5 5 5 5 5 5\n");
                printf("Result: %i\n", r);
                sleep(0.5);
                printf("Sending message: pdr 1 1\n");
                r = protocol_server_send(test_server->server, payload->fd, "pdr 1 1\n");
                printf("Result: %i\n", r);
                sleep(0.5);
                printf("Sending message: sgt 100\n");
                r = protocol_server_send(test_server->server, payload->fd, "sgt 100\n");
                printf("Result: %i\n", r);
                sleep(0.5);
                printf("Sending message: bct 1 1 2 5 5 5 5 5 5 5\n");
                r = protocol_server_send(test_server->server, payload->fd, "bct 1 1 2 5 5 5 5 5 5 5\n");
                printf("Result: %i\n", r);
                sleep(0.5);
                printf("Sending message: pbc 1 MON message\n");
                r = protocol_server_send(test_server->server, payload->fd, "pbc 1 MON message\n");
                printf("Result: %i\n", r);
                sleep(0.5);
                printf("Sending message: enw 1 1 3 2\n");
                r = protocol_server_send(test_server->server, payload->fd, "enw 1 1 3 2\n");
                printf("Result: %i\n", r);
                sleep(0.5);
                while (a < 5) {
                    printf("Sending message: ppo 1 3 2 1\n");
                    r = protocol_server_send(test_server->server, payload->fd, "ppo 1 3 2 1\n");
                    printf("Result: %i\n", r);
                    sleep(5);
                    printf("Sending message: ppo 1 2 2 2\n");
                    r = protocol_server_send(test_server->server, payload->fd, "ppo 1 2 2 2\n");
                    printf("Result: %i\n", r);
                    sleep(1);
                    printf("Sending message: smg message\n");
                    r = protocol_server_send(test_server->server, payload->fd, "smg message %i\n", a);
                    printf("Result: %i\n", r);
                    printf("Sending message: smg message\n");
                    r = protocol_server_send(test_server->server, payload->fd, "smg message %i\n", a + 50);
                    printf("Result: %i\n", r);
                    sleep(1);
                    a++;
                }
                printf("Sending message: seg team1\n");
                r = protocol_server_send(test_server->server, payload->fd, "seg team1\n");
                printf("Result: %i\n", r);
                sleep(1);
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