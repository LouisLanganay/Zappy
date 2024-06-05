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
            printf("Received packet: %s - Type: %i\n", payload->packet.data, payload->packet.type);
            if (a == 0) {
                protocol_packet_t packet = {1, "msz 10 10\n"};
                printf("Sending packet: %s\n", packet.data);
                int r = protocol_server_send_packet(test_server->server, payload->fd, &packet);
                printf("Result: %i\n", r);
                a++;
                sleep(1);
                protocol_packet_t packet2 = {1, "tna team1\n"};
                printf("Sending packet: %s\n", packet2.data);
                r = protocol_server_send_packet(test_server->server, payload->fd, &packet2);
                printf("Result: %i\n", r);
                sleep(1);
                protocol_packet_t packet3 = {1, "tna team2\n"};
                printf("Sending packet: %s\n", packet3.data);
                r = protocol_server_send_packet(test_server->server, payload->fd, &packet3);
                printf("Result: %i\n", r);
                sleep(1);
                protocol_packet_t packet4 = {1, "pnw 1 2 2 1 1 team1\n"};
                printf("Sending packet: %s\n", packet4.data);
                r = protocol_server_send_packet(test_server->server, payload->fd, &packet4);
                printf("Result: %i\n", r);
                sleep(1);
                protocol_packet_t packet5 = {1, "pnw 2 3 3 4 1 team2\n"};
                printf("Sending packet: %s\n", packet5.data);
                r = protocol_server_send_packet(test_server->server, payload->fd, &packet5);
                printf("Result: %i\n", r);
                sleep(1);
                protocol_packet_t packet8 = {1, "pin 1 2 2 5 5 5 5 5 5 5\n"};
                printf("Sending packet: %s\n", packet8.data);
                r = protocol_server_send_packet(test_server->server, payload->fd, &packet8);
                printf("Result: %i\n", r);
                sleep(1);
                protocol_packet_t packet9 = {1, "pdr 1 1\n"};
                printf("Sending packet: %s\n", packet9.data);
                r = protocol_server_send_packet(test_server->server, payload->fd, &packet9);
                printf("Result: %i\n", r);
                sleep(1);
                protocol_packet_t packet10 = {1, "sgt 100\n"};
                printf("Sending packet: %s\n", packet10.data);
                r = protocol_server_send_packet(test_server->server, payload->fd, &packet10);
                printf("Result: %i\n", r);
                sleep(1);
                protocol_packet_t packet11 = {1, "bct 1 1 2 5 5 5 5 5 5 5\n"};
                printf("Sending packet: %s\n", packet11.data);
                r = protocol_server_send_packet(test_server->server, payload->fd, &packet11);
                printf("Result: %i\n", r);
                sleep(1);
                protocol_packet_t packet12 = {1, "pbc 1 MON message\n"};
                printf("Sending packet: %s\n", packet12.data);
                r = protocol_server_send_packet(test_server->server, payload->fd, &packet12);
                printf("Result: %i\n", r);
                sleep(1);
                protocol_packet_t packet13 = {1, "enw 1 1 3 2\n"};
                printf("Sending packet: %s\n", packet13.data);
                r = protocol_server_send_packet(test_server->server, payload->fd, &packet13);
                printf("Result: %i\n", r);
                sleep(1);
                while (a < 5) {
                    protocol_packet_t packet6 = {1, "ppo 1 3 2 1\n"};
                    printf("Sending packet: %s\n", packet6.data);
                    r = protocol_server_send_packet(test_server->server, payload->fd, &packet6);
                    printf("Result: %i\n", r);
                    sleep(5);
                    protocol_packet_t packet7 = {1, "ppo 1 2 2 2\n"};
                    printf("Sending packet: %s\n", packet7.data);
                    r = protocol_server_send_packet(test_server->server, payload->fd, &packet7);
                    printf("Result: %i\n", r);
                    sleep(1);
                    a++;
                }
                protocol_packet_t packet14 = {1, "seg team1\n"};
                printf("Sending packet: %s\n", packet14.data);
                r = protocol_server_send_packet(test_server->server, payload->fd, &packet14);
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
