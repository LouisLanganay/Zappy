#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "server/ai_header.h"

Test(look, check_impossible_look)
{
    zappy_server_t server = {.clients_nb = 5, .height = 11, .width = 10};
    inventory_t sample_tile = {{3, 1, 0, 0, 0, 0, 0}};
    inventory_t sample_tile2 = {{0, 1, 1, 0, 0, 0, 0}};
    inventory_t sample_tile3 = {{0, 0, 0, 0, 0, 0, 0}};
    ai_t ai1 = {.fd = 1, .pos = {5, 5}, .orientation = 5, .level = 1};

    server.map = calloc(11, sizeof(inventory_t *));
    for (int i = 0; i < 11; i++)
        server.map[i] = calloc(10, sizeof(inventory_t));

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);

    server.map[5][5] = sample_tile3;
    server.map[4][4] = sample_tile;
    server.map[4][5] = sample_tile2;
    server.map[4][6] = sample_tile3;

    cr_redirect_stdout();
    look(&server, &ai1, "");
    cr_assert_stdout_eq_str("To client 1:  ]\n");
}

Test(look, check_north_look)
{
    zappy_server_t server = {.clients_nb = 5, .height = 11, .width = 10};
    inventory_t sample_tile = {{3, 1, 0, 0, 0, 0, 0}};
    inventory_t sample_tile2 = {{0, 1, 1, 0, 0, 0, 0}};
    inventory_t sample_tile3 = {{0, 0, 0, 0, 0, 0, 0}};
    ai_t ai1 = {.fd = 1, .pos = {5, 5}, .orientation = NORTH, .level = 1};

    server.map = calloc(11, sizeof(inventory_t *));
    for (int i = 0; i < 11; i++)
        server.map[i] = calloc(10, sizeof(inventory_t));

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);

    server.map[5][5] = sample_tile3;
    server.map[4][4] = sample_tile;
    server.map[4][5] = sample_tile2;
    server.map[4][6] = sample_tile3;

    cr_redirect_stdout();
    look(&server, &ai1, "");
    cr_assert_stdout_eq_str("To client 1: [ player, food food food linemate, linemate deraumere, ]\n");
}

Test(look, check_south_look)
{
    zappy_server_t server = {.clients_nb = 5, .height = 11, .width = 10};
    inventory_t sample_tile = {{0, 1, 0, 0, 0, 1, 1}};
    inventory_t sample_tile2 = {{0, 0, 0, 1, 1, 0, 0}};
    inventory_t sample_tile3 = {{0, 0, 0, 0, 0, 0, 0}};
    ai_t ai1 = {.fd = 1, .pos = {5, 5}, .orientation = SOUTH, .level = 1};

    server.map = calloc(11, sizeof(inventory_t *));
    for (int i = 0; i < 11; i++)
        server.map[i] = calloc(10, sizeof(inventory_t));

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);

    server.map[5][5] = sample_tile3;
    server.map[6][4] = sample_tile;
    server.map[6][5] = sample_tile2;
    server.map[6][6] = sample_tile3;

    cr_redirect_stdout();
    look(&server, &ai1, "");
    cr_assert_stdout_eq_str("To client 1: [ player, linemate phiras thystame, sibur mendiane, ]\n");
}

Test(look, check_east_look)
{
    zappy_server_t server = {.clients_nb = 5, .height = 11, .width = 10};
    inventory_t sample_tile = {{0, 1, 0, 0, 0, 1, 1}};
    inventory_t sample_tile2 = {{0, 0, 0, 1, 1, 0, 0}};
    inventory_t sample_tile3 = {{0, 0, 0, 0, 0, 0, 0}};
    ai_t ai1 = {.fd = 1, .pos = {5, 5}, .orientation = EAST, .level = 1};

    server.map = calloc(11, sizeof(inventory_t *));
    for (int i = 0; i < 11; i++)
        server.map[i] = calloc(10, sizeof(inventory_t));

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);

    server.map[5][5] = sample_tile3;
    server.map[4][6] = sample_tile;
    server.map[5][6] = sample_tile2;
    server.map[6][6] = sample_tile3;

    cr_redirect_stdout();
    look(&server, &ai1, "");
    cr_assert_stdout_eq_str("To client 1: [ player, linemate phiras thystame, sibur mendiane, ]\n");
}

Test(look, check_west_look)
{
    zappy_server_t server = {.clients_nb = 5, .height = 11, .width = 10};
    inventory_t sample_tile = {{0, 1, 0, 0, 0, 1, 1}};
    inventory_t sample_tile2 = {{0, 0, 0, 1, 1, 0, 0}};
    inventory_t sample_tile3 = {{0, 0, 0, 0, 0, 0, 0}};
    ai_t ai1 = {.fd = 1, .pos = {5, 5}, .orientation = WEST, .level = 1};

    server.map = calloc(11, sizeof(inventory_t *));
    for (int i = 0; i < 11; i++)
        server.map[i] = calloc(10, sizeof(inventory_t));

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);

    server.map[5][5] = sample_tile3;
    server.map[4][4] = sample_tile;
    server.map[5][4] = sample_tile2;
    server.map[6][4] = sample_tile3;

    cr_redirect_stdout();
    look(&server, &ai1, "");
    cr_assert_stdout_eq_str("To client 1: [ player, linemate phiras thystame, sibur mendiane, ]\n");
}
