#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "server/gui.h"

Test(smg, check_if_smg_is_correct)
{
    zappy_server_t server = {};
    gui_t gui1 = {.fd = 1};
    gui_t gui2 = {.fd = 2};
    gui_t gui3 = {.fd = 3};

    TAILQ_INIT(&server.guis);
    TAILQ_INSERT_TAIL(&server.guis, &gui1, entries);
    TAILQ_INSERT_TAIL(&server.guis, &gui2, entries);
    TAILQ_INSERT_TAIL(&server.guis, &gui3, entries);

    cr_redirect_stdout();
    smg(&server, "Hello World!");
    cr_assert_stdout_eq_str(
        "To client 1: smg Hello World!\n"
        "To client 2: smg Hello World!\n"
        "To client 3: smg Hello World!\n");
}
