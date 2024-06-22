#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "server/ai_header.h"

Test(inventory, check_inventory_display)
{
    zappy_server_t server = {.clients_nb = 5};
    inventory_t player_inventory = {300, 1, 5, 3, 4, 0, 6};
    ai_t ai1 = {.fd = 1, .inventory = player_inventory};

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);

    cr_redirect_stdout();
    inventory(&server, &ai1, "");
    cr_assert_stdout_eq_str("To client 1: [food 300, sibur 3, linemate 1, deraumere 5, mendiane 4, phiras 0, thystame 6]\n");
}
