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
            protocol_packet_t packet;
            printf("Type: %i\n", payload->packet.type);
            if (payload->packet.type == 26) {
                map_size_t map_size = {10, 10};
                printf("Sending packet: %i\n", EVT_MAP_SIZE);
                packet.type = EVT_MAP_SIZE;
                memcpy(packet.data, &map_size, sizeof(map_size_t));
                int r = protocol_server_send_packet(test_server->server, payload->fd, &packet);
                printf("Result: %i\n", r);

                sleep(1);

                protocol_packet_t packet2;
                player_add_t player_add = {1, 1, 1, 1, 1, "test"};
                packet2.type = EVT_PLAYER_ADD;
                memcpy(packet2.data, &player_add, sizeof(player_add_t));
                printf("Sending packet: %i\n", EVT_PLAYER_ADD);
                r = protocol_server_send_packet(test_server->server, payload->fd, &packet2);
                printf("Result: %i\n", r);

                sleep(1);

                protocol_packet_t packet3;
                player_inventory_t player_inventory = {1, {1, 1, 1, 1, 1, 1, 1}};
                packet3.type = EVT_PLAYER_INVENTORY;
                memcpy(packet3.data, &player_inventory, sizeof(player_inventory_t));
                printf("Sending packet: %i\n", EVT_PLAYER_INVENTORY);
                r = protocol_server_send_packet(test_server->server, payload->fd, &packet3);
                printf("Result: %i\n", r);

                sleep(1);

                protocol_packet_t packet4;
                tile_content_t tile_content = {5, 2, {5, 1, 2, 1, 3, 1, 1}};
                packet4.type = EVT_TILE_CONTENT;
                memcpy(packet4.data, &tile_content, sizeof(tile_content_t));
                printf("Sending packet: %i\n", EVT_TILE_CONTENT);
                r = protocol_server_send_packet(test_server->server, payload->fd, &packet4);
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
