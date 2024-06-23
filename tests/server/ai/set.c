#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "server/ai_header.h"

Test(set, check_basic_set)
{
    zappy_server_t server = {.clients_nb = 5, .height = 11, .width = 10};
    inventory_t sample_tile = {{0, 1, 0, 0, 0, 1, 1}};
    ai_t ai1 = {.fd = 1, .pos = {5, 5}, .orientation = SOUTH, .level = 1, .inventory = sample_tile};

    server.map = calloc(11, sizeof(inventory_t *));
    for (int i = 0; i < 11; i++)
        server.map[i] = calloc(10, sizeof(inventory_t));

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);

    server.map[5][5] = sample_tile;

    cr_redirect_stdout();
    set(&server, &ai1, " linemate");
    cr_assert_stdout_eq_str("To client 1: ok\n");
    cr_assert_eq(2, server.map[5][5].linemate);
    cr_assert_eq(0, ai1.inventory.linemate);
}

Test(set, check_invalid_arg)
{
    zappy_server_t server = {.clients_nb = 5, .height = 11, .width = 10};
    inventory_t sample_tile = {{0, 1, 0, 0, 0, 1, 1}};
    ai_t ai1 = {.fd = 1, .pos = {5, 5}, .orientation = SOUTH, .level = 1, .inventory = sample_tile};

    server.map = calloc(11, sizeof(inventory_t *));
    for (int i = 0; i < 11; i++)
        server.map[i] = calloc(10, sizeof(inventory_t));

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);

    server.map[5][5] = sample_tile;

    cr_redirect_stdout();
    set(&server, &ai1, " hello");
    cr_assert_stdout_eq_str("To client 1: ko\n");
}

Test(set, check_not_enough_ressources)
{
    zappy_server_t server = {.clients_nb = 5, .height = 11, .width = 10};
    inventory_t sample_tile = {{0, 0, 0, 0, 0, 1, 1}};
    ai_t ai1 = {.fd = 1, .pos = {5, 5}, .orientation = SOUTH, .level = 1, .inventory = sample_tile};

    server.map = calloc(11, sizeof(inventory_t *));
    for (int i = 0; i < 11; i++)
        server.map[i] = calloc(10, sizeof(inventory_t));

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);

    server.map[5][5] = sample_tile;

    cr_redirect_stdout();
    set(&server, &ai1, " linemate");
    cr_assert_stdout_eq_str("To client 1: ko\n");
}
