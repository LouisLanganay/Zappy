#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "server/ai_header.h"

Test(connect_nbr, check_default_teams_slots_nb)
{
    zappy_server_t server = {.clients_nb = 5};
    team_t team = {.name = "Team1"};

    TAILQ_INIT(&server.teams);
    TAILQ_INSERT_TAIL(&server.teams, &team, entries);

    ai_t ai1 = {.fd = 1, .team = &team};

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);

    cr_redirect_stdout();
    connect_nbr(&server, &ai1, "");
    cr_assert_stdout_eq_str("To client 1: 4\n");
}
