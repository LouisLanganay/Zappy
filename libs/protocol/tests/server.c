/*
** EPITECH PROJECT, 2024
** Protocol
** File description:
** protocol/test/server
*/

#include <stdlib.h>
#include <stdio.h>

#include "protocol/server.h"

static void handle_payload(
    protocol_server_t *server,
    const protocol_payload_t *payload)
{
    char *message = protocol_receive_message(payload);

    if (!message)
        return;
    printf("Received packet: %s\n", message);
    protocol_server_send_message(server, payload->fd,
        "Hello from %s!", "server");
    free(message);
}

int main(void)
{
    protocol_server_t *server = protocol_server_create(4242);
    protocol_payload_t *payload;

    if (!server)
        return EXIT_FAILURE;
    printf("Server started\n");
    while (protocol_server_is_open()) {
        protocol_server_listen(server);
        while (!TAILQ_EMPTY(&server->payloads)) {
            payload = TAILQ_FIRST(&server->payloads);
            TAILQ_REMOVE(&server->payloads, payload, entries);
            handle_payload(server, payload);
            free(payload);
        }
    }
    protocol_server_close(server);
    printf("Server closed\n");
    return EXIT_SUCCESS;
}
