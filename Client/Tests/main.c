/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** main
*/

#include "test_server.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int port = atoi(argv[1]);
    test_server_t *server = test_server_create(port);
    if (!server) {
        fprintf(stderr, "Failed to create server on port %d\n", port);
        return EXIT_FAILURE;
    }

    test_server_run(server);
    test_server_destroy(server);

    return EXIT_SUCCESS;
}
