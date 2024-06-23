#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "server/gui.h"

Test(mct, check_if_mct_is_correct)
{
    zappy_server_t server = {.width = 4, .height = 4, .map = malloc(sizeof(inventory_t *) * 4)};

    if (!server.map)
        return;
    for (uint8_t i = 0; i < 4; i++) {
        server.map[i] = malloc(sizeof(inventory_t) * 4);
        if (!server.map[i])
            return;
        for (uint8_t j = 0; j < 4; j++)
            server.map[i][j] = (inventory_t){.food = 1,
                .linemate = 2, .deraumere = 0, .sibur = 1,
                .mendiane = 0, .phiras = 1, .thystame = 2};
    }

    cr_redirect_stdout();
    mct(&server, 0, NULL);
    cr_assert_stdout_eq_str(
        "To client 0: bct 0 0 1 2 0 1 0 1 2\n"
        "To client 0: bct 0 1 1 2 0 1 0 1 2\n"
        "To client 0: bct 0 2 1 2 0 1 0 1 2\n"
        "To client 0: bct 0 3 1 2 0 1 0 1 2\n"
        "To client 0: bct 1 0 1 2 0 1 0 1 2\n"
        "To client 0: bct 1 1 1 2 0 1 0 1 2\n"
        "To client 0: bct 1 2 1 2 0 1 0 1 2\n"
        "To client 0: bct 1 3 1 2 0 1 0 1 2\n"
        "To client 0: bct 2 0 1 2 0 1 0 1 2\n"
        "To client 0: bct 2 1 1 2 0 1 0 1 2\n"
        "To client 0: bct 2 2 1 2 0 1 0 1 2\n"
        "To client 0: bct 2 3 1 2 0 1 0 1 2\n"
        "To client 0: bct 3 0 1 2 0 1 0 1 2\n"
        "To client 0: bct 3 1 1 2 0 1 0 1 2\n"
        "To client 0: bct 3 2 1 2 0 1 0 1 2\n"
        "To client 0: bct 3 3 1 2 0 1 0 1 2\n");
}
