#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "server/gui.h"

Test(sst, check_if_sst_is_correct)
{
    zappy_server_t server = {.freq = 10};
    gui_t gui1 = {.fd = 1};
    gui_t gui2 = {.fd = 2};
    gui_t gui3 = {.fd = 3};

    TAILQ_INIT(&server.guis);
    TAILQ_INSERT_TAIL(&server.guis, &gui1, entries);
    TAILQ_INSERT_TAIL(&server.guis, &gui2, entries);
    TAILQ_INSERT_TAIL(&server.guis, &gui3, entries);

    cr_redirect_stdout();
    sst(&server, 0, " 5");
    cr_assert_eq(server.freq, 5);
    cr_assert_stdout_eq_str(
        "To client 1: sst 5\n"
        "To client 2: sst 5\n"
        "To client 3: sst 5\n");
}

Test(sst, sst_missing_arg)
{
    zappy_server_t server = {.freq = 10};
    gui_t gui1 = {.fd = 1};
    gui_t gui2 = {.fd = 2};
    gui_t gui3 = {.fd = 3};

    TAILQ_INIT(&server.guis);
    TAILQ_INSERT_TAIL(&server.guis, &gui1, entries);
    TAILQ_INSERT_TAIL(&server.guis, &gui2, entries);
    TAILQ_INSERT_TAIL(&server.guis, &gui3, entries);

    cr_redirect_stdout();
    sst(&server, 0, "");
    cr_assert_stdout_eq_str("To client 0: sbp\n");
}
