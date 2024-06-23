#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "server/gui.h"

Test(ppo, check_if_ppo_is_correct)
{
    zappy_server_t server = {};
    ai_t ai = {.id = 1, .pos = {1, 5}, .orientation = NORTH};

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai, entries);

    cr_redirect_stdout();
    ppo(&server, 0, " 1");
    cr_assert_stdout_eq_str("To client 0: ppo 1 1 5 1\n");
}

Test(ppo, missing_args)
{
    zappy_server_t server = {};

    TAILQ_INIT(&server.ais);

    cr_redirect_stdout();
    ppo(&server, 0, "");
    cr_assert_stdout_eq_str("To client 0: sbp\n");
}

Test(ppo, missing_ai)
{
    zappy_server_t server = {};

    TAILQ_INIT(&server.ais);

    cr_redirect_stdout();
    ppo(&server, 0, " 1");
    cr_assert_stdout_eq_str("To client 0: sbp\n");
}
