#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "server/gui.h"

Test(enw, check_if_edi_is_correct)
{
    zappy_server_t server = {};
    ai_t ai = {.id = 5, .pos = {4, 2}};
    gui_t gui1 = {.fd = 1};
    gui_t gui2 = {.fd = 2};
    gui_t gui3 = {.fd = 3};

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai, entries);
    TAILQ_INIT(&server.guis);
    TAILQ_INSERT_TAIL(&server.guis, &gui1, entries);
    TAILQ_INSERT_TAIL(&server.guis, &gui2, entries);
    TAILQ_INSERT_TAIL(&server.guis, &gui3, entries);

    cr_redirect_stdout();
    enw(&server, &ai, 1);
    cr_assert_stdout_eq_str(
        "To client 1: enw 1 5 4 2\n"
        "To client 2: enw 1 5 4 2\n"
        "To client 3: enw 1 5 4 2\n");
}
