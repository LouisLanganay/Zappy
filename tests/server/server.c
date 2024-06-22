#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "server.h"

Test(zappy_server, create_server)
{
    zappy_server_t server = {};

    server_create(&server);
    cr_assert_eq(server.port, 4242);
    cr_assert_eq(server.width, 10);
    cr_assert_eq(server.height, 10);
    cr_assert_eq(server.clients_nb, 5);
    cr_assert_eq(server.freq, 100);
    cr_assert_eq(server.verbose, false);
    cr_assert_eq(server.socket, NULL);
    cr_assert_eq(server.map, NULL);
    cr_assert_eq(TAILQ_EMPTY(&server.ais), true);
    cr_assert_eq(TAILQ_EMPTY(&server.teams), true);
    cr_assert_eq(TAILQ_EMPTY(&server.guis), true);
}

Test(zappy_server, run_server)
{
    zappy_server_t server = {};
    team_t team = {.name = "Team1"};
    server_create(&server);
    TAILQ_INSERT_TAIL(&server.teams, &team, entries);

    cr_redirect_stdout();
    zappy_server(&server);
    cr_assert_stdout_eq_str(
        "===================Zappy Server===================\n"
        "port = 4242\n"
        "width = 10\n"
        "height = 10\n"
        "clients_nb = 5\n"
        "freq = 100\n"
        "Teams [0]:\n"
        "\t0: Team1\n"
        "verbose = false\n"
        "==================================================\n");
}

Test(zappy_server, run_server_verbose)
{
    zappy_server_t server = {};
    server_create(&server);
    server.verbose = true;

    team_t team = {.name = "Team1"};
    TAILQ_INSERT_TAIL(&server.teams, &team, entries);

    cr_redirect_stdout();
    zappy_server(&server);
    cr_assert_stdout_eq_str(
        "===================Zappy Server===================\n"
        "port = 4242\n"
        "width = 10\n"
        "height = 10\n"
        "clients_nb = 5\n"
        "freq = 100\n"
        "Teams [0]:\n"
        "\t0: Team1\n"
        "verbose = true\n"
        "==================================================\n"
        "Meteor shower\n");
}

Test(zappy_server, run_server_to_low_port)
{
    zappy_server_t server = {};
    server_create(&server);
    server.port = 0;

    cr_assert_eq(zappy_server(&server), false);
}

Test(zappy_server, run_server_to_low_width)
{
    zappy_server_t server = {};
    server_create(&server);
    server.width = 0;

    cr_assert_eq(zappy_server(&server), false);
}

Test(zappy_server, run_server_to_low_height)
{
    zappy_server_t server = {};
    server_create(&server);
    server.height = 0;

    cr_assert_eq(zappy_server(&server), false);
}

Test(zappy_server, run_server_to_low_clients_nb)
{
    zappy_server_t server = {};
    server_create(&server);
    server.clients_nb = 0;

    cr_assert_eq(zappy_server(&server), false);
}

Test(zappy_server, run_server_to_low_freq)
{
    zappy_server_t server = {};
    server_create(&server);
    server.freq = 0;

    cr_assert_eq(zappy_server(&server), false);
}
