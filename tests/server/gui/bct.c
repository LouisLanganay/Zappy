#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "server/gui.h"

Test(bct, check_if_bct_is_correct)
{
    zappy_server_t server = {.width = 10, .height = 10, .map = malloc(sizeof(inventory_t *) * 10)};

    if (!server.map)
        return;
    for (uint8_t i = 0; i < 10; i++) {
        server.map[i] = malloc(sizeof(inventory_t) * 10);
        if (!server.map[i])
            return;
        for (uint8_t j = 0; j < 10; j++)
            server.map[i][j] = (inventory_t){.food = 1,
                .linemate = 2, .deraumere = 3, .sibur = 4,
                .mendiane = 5, .phiras = 6, .thystame = 7};
    }

    cr_redirect_stdout();
    bct(&server, 0, " 1 1");
    cr_assert_stdout_eq_str("To client 0: bct 1 1 1 2 3 4 5 6 7\n");
}

Test(bct, check_if_bct_x_is_to_high)
{
    zappy_server_t server = {.width = 10, .height = 10, .map = malloc(sizeof(inventory_t *) * 10)};

    if (!server.map)
        return;
    for (uint8_t i = 0; i < 10; i++) {
        server.map[i] = malloc(sizeof(inventory_t) * 10);
        if (!server.map[i])
            return;
        for (uint8_t j = 0; j < 10; j++)
            server.map[i][j] = (inventory_t){.food = 1,
                .linemate = 2, .deraumere = 3, .sibur = 4,
                .mendiane = 5, .phiras = 6, .thystame = 7};
    }

    cr_redirect_stdout();
    bct(&server, 0, " 10 5");
    cr_assert_stdout_eq_str("To client 0: sbp\n");
}

Test(bct, check_if_bct_y_is_to_high)
{
    zappy_server_t server = {.width = 10, .height = 10, .map = malloc(sizeof(inventory_t *) * 10)};

    if (!server.map)
        return;
    for (uint8_t i = 0; i < 10; i++) {
        server.map[i] = malloc(sizeof(inventory_t) * 10);
        if (!server.map[i])
            return;
        for (uint8_t j = 0; j < 10; j++)
            server.map[i][j] = (inventory_t){.food = 1,
                .linemate = 2, .deraumere = 3, .sibur = 4,
                .mendiane = 5, .phiras = 6, .thystame = 7};
    }

    cr_redirect_stdout();
    bct(&server, 0, " 5 10");
    cr_assert_stdout_eq_str("To client 0: sbp\n");
}

Test(bct, check_if_bct_is_missing_args)
{
    zappy_server_t server = {.width = 10, .height = 10, .map = malloc(sizeof(inventory_t *) * 10)};

    if (!server.map)
        return;
    for (uint8_t i = 0; i < 10; i++) {
        server.map[i] = malloc(sizeof(inventory_t) * 10);
        if (!server.map[i])
            return;
        for (uint8_t j = 0; j < 10; j++)
            server.map[i][j] = (inventory_t){.food = 1,
                .linemate = 2, .deraumere = 3, .sibur = 4,
                .mendiane = 5, .phiras = 6, .thystame = 7};
    }

    cr_redirect_stdout();
    bct(&server, 0, " 1");
    cr_assert_stdout_eq_str("To client 0: sbp\n");
}
