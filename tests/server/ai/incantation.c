#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "server/ai_header.h"

Test(incantation, check_not_enough_ressources)
{
    zappy_server_t server = {.clients_nb = 5, .height = 11, .width = 10};
    inventory_t sample_tile = {{0, 0, 0, 0, 0, 0, 0}};
    ai_t ai1 = {.fd = 1, .pos = {5, 5}, .orientation = 5, .level = 1, .inventory = {{10, 10, 10, 10, 10, 10, 10}}};

    server.map = calloc(11, sizeof(inventory_t *));
    for (int i = 0; i < 11; i++)
        server.map[i] = calloc(10, sizeof(inventory_t));

    TAILQ_INIT(&server.ais);
    TAILQ_INIT(&ai1.incantations);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);

    server.map[5][5] = sample_tile;

    cr_assert(!can_incantation(&server, &ai1, ""));
}
