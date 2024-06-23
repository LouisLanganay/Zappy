#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "server/gui.h"

Test(pie, check_if_pie_is_correct)
{
    zappy_server_t server = {};
    ai_t ai = {.id = 1, .pos = {1, 5}, .orientation = NORTH};
    gui_t gui1 = {.fd = 1};
    gui_t gui2 = {.fd = 2};
    gui_t gui3 = {.fd = 3};

    TAILQ_INIT(&server.guis);
    TAILQ_INSERT_TAIL(&server.guis, &gui1, entries);
    TAILQ_INSERT_TAIL(&server.guis, &gui2, entries);
    TAILQ_INSERT_TAIL(&server.guis, &gui3, entries);

    cr_redirect_stdout();
    pie(&server, &ai);
    cr_assert_stdout_eq_str(
        "To client 1: pie 1 5 1\n"
        "To client 2: pie 1 5 1\n"
        "To client 3: pie 1 5 1\n");
}
