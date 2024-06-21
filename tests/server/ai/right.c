#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "server/ai_header.h"

Test(right, check_player_270_rotation)
{
    zappy_server_t server = {.clients_nb = 5, .height = 11, .width = 10};

    ai_t ai1 = {.fd = 1, .pos = {0, 0}, .orientation = WEST};

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);

    cr_redirect_stdout();
    for (int i = 1; i < 4; i++) {
        right(&server, &ai1, "");
        cr_assert_eq(ai1.orientation, i % 4);
    }
}

Test(right, check_player_basic_rotation)
{
    zappy_server_t server = {.clients_nb = 5, .height = 11, .width = 10};

    ai_t ai1 = {.fd = 1, .pos = {0, 0}, .orientation = SOUTH};

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);

    cr_redirect_stdout();
    right(&server, &ai1, "");
    cr_assert_eq(ai1.orientation, WEST);
    cr_assert_stdout_eq_str("To client 1: ok\n");
}

Test(right, check_player_impossible_rotation)
{
    zappy_server_t server = {.clients_nb = 5, .height = 11, .width = 10};

    ai_t ai1 = {.fd = 1, .pos = {0, 0}, .orientation = 5};

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);

    cr_redirect_stdout();
    right(&server, &ai1, "");
    cr_assert_eq(ai1.orientation, 5);
    cr_assert_stdout_eq_str("To client 1: ok\n");
}
