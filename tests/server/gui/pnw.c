#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "server/gui.h"

Test(pnw, check_if_pnw_is_correct)
{
    zappy_server_t server = {};
    team_t team = {.name = "team"};
    ai_t ai = {.id = 1, .pos = {1, 5}, .orientation = NORTH, .level = 1, .team = &team};
    gui_t gui1 = {.fd = 1};
    gui_t gui2 = {.fd = 2};
    gui_t gui3 = {.fd = 3};

    TAILQ_INIT(&server.guis);
    TAILQ_INSERT_TAIL(&server.guis, &gui1, entries);
    TAILQ_INSERT_TAIL(&server.guis, &gui2, entries);
    TAILQ_INSERT_TAIL(&server.guis, &gui3, entries);

    cr_redirect_stdout();
    pnw(&server, &ai);
    cr_assert_stdout_eq_str(
        "To client 1: pnw 1 1 5 1 1 team\n"
        "To client 2: pnw 1 1 5 1 1 team\n"
        "To client 3: pnw 1 1 5 1 1 team\n");
}
