#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "server/gui.h"

Test(tna, check_if_tna_is_correct)
{
    zappy_server_t server = {};
    team_t team = {.name = "team1"};
    team_t team2 = {.name = "team2"};
    team_t team3 = {.name = "team3"};

    TAILQ_INIT(&server.teams);
    TAILQ_INSERT_TAIL(&server.teams, &team, entries);
    TAILQ_INSERT_TAIL(&server.teams, &team2, entries);
    TAILQ_INSERT_TAIL(&server.teams, &team3, entries);

    cr_redirect_stdout();
    tna(&server, 0, "");
    cr_assert_stdout_eq_str(
        "To client 0: tna team1\n"
        "To client 0: tna team2\n"
        "To client 0: tna team3\n");
}
