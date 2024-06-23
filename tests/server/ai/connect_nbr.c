#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "server/ai_header.h"

Test(connect_nbr, check_default_teams_slots_nb)
{
    zappy_server_t server = {.clients_nb = 5};
    team_t team = {.name = "Team1", .slots = server.clients_nb};

    TAILQ_INIT(&server.teams);
    TAILQ_INSERT_TAIL(&server.teams, &team, entries);

    ai_t ai = {.fd = 1, .team = &team};

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai, entries);
    ai.team->slots--;

    cr_redirect_stdout();
    connect_nbr(&server, &ai, "");
    cr_assert_stdout_eq_str("To client 1: 4\n");
}
