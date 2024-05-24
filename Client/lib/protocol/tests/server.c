/*
** EPITECH PROJECT, 2024
** Protocol
** File description:
** protocol/test/server
*/

#include <stdlib.h>
#include <stdio.h>

#include "protocol/server.h"

int main(void)
{
    protocol_server_t *server = protocol_server_create(4242);
    protocol_payload_t *payload;
    const protocol_packet_t server_payload = {0, "Hello from server!"};

    if (!server)
        return EXIT_FAILURE;
    printf("Server started\n");
    while (protocol_server_is_open()) {
        protocol_server_listen(server);
        while (!TAILQ_EMPTY(&server->payloads)) {
            payload = TAILQ_FIRST(&server->payloads);
            TAILQ_REMOVE(&server->payloads, payload, entries);
            printf("Received packet: %s\n", (char *)payload->packet.data);
            protocol_server_send_packet(&server_payload, payload->fd, server);
            free(payload);
        }
    }
    protocol_server_close(server);
    printf("Server closed\n");
    return EXIT_SUCCESS;
}
