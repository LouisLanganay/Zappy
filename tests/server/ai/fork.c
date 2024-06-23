#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "server/ai_header.h"

Test(fork, check_fork_output)
{
    zappy_server_t server = {.clients_nb = 5, .height = 11, .width = 10};
    ai_t ai1 = {.fd = 1, .pos = {5, 5}, .orientation = SOUTH};

    TAILQ_INIT(&server.eggs);
    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);

    cr_redirect_stdout();
    exec_fork(&server, &ai1, "");
    cr_assert(can_fork(&server, &ai1, ""));
    cr_assert_stdout_eq_str("To client 1: ok\n");
}

Test(fork, check_egg_creation)
{
    zappy_server_t server = {.clients_nb = 5, .height = 11, .width = 10};
    ai_t ai1 = {.fd = 1, .pos = {5, 5}, .orientation = SOUTH};
    egg_t *egg;

    TAILQ_INIT(&server.eggs);
    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);

    cr_redirect_stdout();
    exec_fork(&server, &ai1, "");
    cr_assert(can_fork(&server, &ai1, ""));
    egg = TAILQ_FIRST(&server.eggs);
    cr_assert_eq(egg->pos.x, 5);
    cr_assert_eq(egg->pos.y, 5);
}
