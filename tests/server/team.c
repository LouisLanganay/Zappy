#include <criterion/criterion.h>

#include "server.h"

Test(team_get_by_name, check_if_team_is_found) {
    zappy_server_t server = {0};
    team_t team = {.id = 1, .name = "Team1"};

    TAILQ_INIT(&server.teams);
    TAILQ_INSERT_TAIL(&server.teams, &team, entries);
    cr_assert_eq(team_get_by_name(&server, "Team1"), &team);
}

Test(team_get_by_name, check_if_team_is_not_found) {
    zappy_server_t server = {0};
    team_t team = {.id = 1, .name = "Team1"};

    TAILQ_INIT(&server.teams);
    TAILQ_INSERT_TAIL(&server.teams, &team, entries);
    cr_assert_eq(team_get_by_name(&server, "Team2"), NULL);
}

Test(team_get_by_name, empty_teams) {
    zappy_server_t server = {0};

    TAILQ_INIT(&server.teams);
    cr_assert_eq(team_get_by_name(&server, "Team1"), NULL);
}

Test(team_get_by_id, check_if_team_is_found) {
    zappy_server_t server = {0};
    team_t team = {.id = 1, .name = "Team1"};

    TAILQ_INIT(&server.teams);
    TAILQ_INSERT_TAIL(&server.teams, &team, entries);
    cr_assert_eq(team_get_by_id(&server, 1), &team);
}

Test(team_get_by_id, check_if_team_is_not_found) {
    zappy_server_t server = {0};
    team_t team = {.id = 1, .name = "Team1"};

    TAILQ_INIT(&server.teams);
    TAILQ_INSERT_TAIL(&server.teams, &team, entries);
    cr_assert_eq(team_get_by_id(&server, 2), NULL);
}

Test(team_get_by_id, empty_teams) {
    zappy_server_t server = {0};

    TAILQ_INIT(&server.teams);
    cr_assert_eq(team_get_by_id(&server, 1), NULL);
}
