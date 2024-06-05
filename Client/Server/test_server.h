/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** test_server
*/

#ifndef TEST_SERVER_H
#define TEST_SERVER_H

#include "../../libs/protocol/include/protocol/server.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    protocol_server_t *server;
} test_server_t;

test_server_t *test_server_create(int port);
void test_server_run(test_server_t *test_server);
void test_server_destroy(test_server_t *test_server);

#endif // TEST_SERVER_H
