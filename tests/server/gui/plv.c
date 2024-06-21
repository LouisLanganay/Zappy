#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "server/gui.h"

Test(plv, check_if_plv_is_correct)
{
    zappy_server_t server = {};
    ai_t ai = {.id = 1, .level = 2};

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai, entries);

    cr_redirect_stdout();
    plv(&server, 0, " 1");
    cr_assert_stdout_eq_str("To client 0: plv 1 2\n");
}

Test(plv, missing_args)
{
    zappy_server_t server = {};

    TAILQ_INIT(&server.ais);

    cr_redirect_stdout();
    plv(&server, 0, "");
    cr_assert_stdout_eq_str("To client 0: sbp\n");
}

Test(plv, missing_ai)
{
    zappy_server_t server = {};

    TAILQ_INIT(&server.ais);

    cr_redirect_stdout();
    plv(&server, 0, " 1");
    cr_assert_stdout_eq_str("To client 0: sbp\n");
}
