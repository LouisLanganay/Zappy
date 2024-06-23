#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "server/gui.h"

Test(pin, check_if_pin_is_correct)
{
    zappy_server_t server = {};
    ai_t ai = {.id = 1, .pos = {2, 5}, .inventory = {{0, 2, 0, 4, 0, 1, 3}}};

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai, entries);

    cr_redirect_stdout();
    pin(&server, 0, " 1");
    cr_assert_stdout_eq_str("To client 0: pin 1 2 5 0 2 0 4 0 1 3\n");
}

Test(pin, missing_args)
{
    zappy_server_t server = {};

    TAILQ_INIT(&server.ais);

    cr_redirect_stdout();
    pin(&server, 0, "");
    cr_assert_stdout_eq_str("To client 0: sbp\n");
}

Test(pin, missing_ai)
{
    zappy_server_t server = {};

    TAILQ_INIT(&server.ais);

    cr_redirect_stdout();
    pin(&server, 0, " 1");
    cr_assert_stdout_eq_str("To client 0: sbp\n");
}
