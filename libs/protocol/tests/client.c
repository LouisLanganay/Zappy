/*
** EPITECH PROJECT, 2024
** Protocol
** File description:
** protocol/test/client
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#include "protocol/client.h"

static bool is_open(
    const bool close)
{
    static bool state = true;

    if (close)
        state = false;
    return state;
}

static void handle_signal(const int sig)
{
    if (sig != SIGINT)
        return;
    write(1, "\r", 1);
    is_open(true);
}

static void setup_signal(void)
{
    struct sigaction sig = {0};

    signal(SIGPIPE, SIG_IGN);
    sig.sa_handler = handle_signal;
    sigaction(SIGINT, &sig, NULL);
}

int main(void)
{
    protocol_client_t *client = protocol_client_create("127.0.0.1", 4242);
    protocol_payload_t *payload;

    if (!client)
        return EXIT_FAILURE;
    printf("Client started\n");
    setup_signal();
    protocol_client_send(client, "GRAPHIC");
    while (is_open(false) && protocol_client_is_connected(client)) {
        protocol_client_listen(client);
        while (!TAILQ_EMPTY(&client->payloads)) {
            payload = TAILQ_FIRST(&client->payloads);
            TAILQ_REMOVE(&client->payloads, payload, entries);
            printf("Received packet: %s\n", payload->message);
            free(payload);
        }
    }
    protocol_client_close(client);
    printf("Client closed\n");
    return EXIT_SUCCESS;
}
