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

Test(team_get_empty_slots, check_empty_slots) {
    zappy_server_t server = {.clients_nb = 4};
    team_t team = {.id = 1, .name = "Team1"};
    ai_t ai1 = {.team = &team};
    ai_t ai2 = {.team = &team};

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);
    TAILQ_INSERT_TAIL(&server.ais, &ai2, entries);
    cr_assert_eq(team_get_empty_slots(&server, &team), 2);
}

Test(team_get_empty_slots, check_empty_slots_with_no_ais) {
    zappy_server_t server = {.clients_nb = 4};
    team_t team = {.id = 1, .name = "Team1"};

    TAILQ_INIT(&server.ais);
    cr_assert_eq(team_get_empty_slots(&server, &team), 4);
}

Test(team_get_empty_slots, check_empty_slots_with_no_team) {
    zappy_server_t server = {.clients_nb = 4};
    team_t team = {.id = 1, .name = "Team1"};
    ai_t ai1 = {.team = &team};
    ai_t ai2 = {.team = &team};

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);
    TAILQ_INSERT_TAIL(&server.ais, &ai2, entries);
    cr_assert_eq(team_get_empty_slots(&server, NULL), 0);
}

Test(team_get_empty_slots, check_empty_slots_with_no_clients) {
    zappy_server_t server = {.clients_nb = 0};
    team_t team = {.id = 1, .name = "Team1"};
    ai_t ai1 = {.team = &team};
    ai_t ai2 = {.team = &team};

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);
    TAILQ_INSERT_TAIL(&server.ais, &ai2, entries);
    cr_assert_eq(team_get_empty_slots(&server, &team), 0);
}

Test(team_get_empty_slots, other_team) {
    zappy_server_t server = {.clients_nb = 4};
    team_t team1 = {.id = 1, .name = "Team1"};
    team_t team2 = {.id = 2, .name = "Team2"};
    ai_t ai1 = {.team = &team1};
    ai_t ai2 = {.team = &team1};
    ai_t ai3 = {.team = &team2};

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);
    TAILQ_INSERT_TAIL(&server.ais, &ai2, entries);
    TAILQ_INSERT_TAIL(&server.ais, &ai3, entries);
    cr_assert_eq(team_get_empty_slots(&server, &team1), 2);
}
