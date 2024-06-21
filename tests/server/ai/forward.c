#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "server/ai_header.h"

Test(forward, check_forward_message)
{
    zappy_server_t server = {.clients_nb = 5, .height = 11, .width = 10};

    ai_t ai1 = {.fd = 1, .pos = {0, 0}, .orientation = EAST};

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);

    cr_redirect_stdout();
    forward(&server, &ai1, "");
    cr_assert_stdout_eq_str("To client 1: ok\n");
}

Test(forward, check_basic_movement)
{
    zappy_server_t server = {.clients_nb = 5, .height = 11, .width = 10};

    ai_t ai1 = {.fd = 1, .pos = {0, 0}, .orientation = SOUTH};

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);

    cr_redirect_stdout();
    forward(&server, &ai1, "");
    cr_assert_eq(ai1.pos.y, 1);
}

Test(forward, check_across_border_movement)
{
    zappy_server_t server = {.clients_nb = 5, .height = 11, .width = 10};

    ai_t ai1 = {.fd = 1, .pos = {0, 0}, .orientation = NORTH};

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);

    cr_redirect_stdout();
    forward(&server, &ai1, "");
    cr_assert_eq(ai1.pos.y, 10);
}

Test(forward, check_horizontal_movement_1)
{
    zappy_server_t server = {.clients_nb = 5, .height = 11, .width = 10};

    ai_t ai1 = {.fd = 1, .pos = {0, 0}, .orientation = EAST};

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);

    cr_redirect_stdout();
    forward(&server, &ai1, "");
    cr_assert_eq(ai1.pos.x, 1);
}

Test(forward, check_horizontal_movement_2)
{
    zappy_server_t server = {.clients_nb = 5, .height = 11, .width = 10};

    ai_t ai1 = {.fd = 1, .pos = {0, 0}, .orientation = WEST};

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);

    cr_redirect_stdout();
    forward(&server, &ai1, "");
    cr_assert_eq(ai1.pos.x, 9);
}

Test(forward, check_impossible_orientation)
{
    zappy_server_t server = {.clients_nb = 5, .height = 11, .width = 10};

    ai_t ai1 = {.fd = 1, .pos = {0, 0}, .orientation = 5};

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);

    cr_redirect_stdout();
    forward(&server, &ai1, "");
    cr_assert_stdout_eq_str("To client 1: ok\n");
    cr_assert_eq(ai1.pos.x, 0);
    cr_assert_eq(ai1.pos.y, 0);
}
