#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>

#include "server/game.h"

static zappy_server_t *test_create_server(void)
{
    zappy_server_t *server = calloc(1, sizeof(zappy_server_t));

    if (!server)
        cr_assert_fail();
    server_create(server);
    server->verbose = true;
    server->clients_nb = 5;
    server->width = 3;
    server->height = 3;
    server->freq = 5;
    server->map = calloc(server->height, sizeof(inventory_t *));
    if (!server->map)
        cr_assert_fail();
    for (uint16_t y = 0; y < server->height; ++y) {
        server->map[y] = calloc(server->width, sizeof(inventory_t));
        if (!server->map[y])
            cr_assert_fail();
        for (uint16_t x = 0; x < server->width; ++x) {
            server->map[y][x] = (inventory_t){ .food = 0, .linemate = 0,
                .deraumere = 0, .sibur = 0, .mendiane = 0, .phiras = 0,
                .thystame = 0 };
        }
    }
    server->socket = protocol_server_create(server->port);
    if (!server->socket)
        cr_assert_fail();
    return server;
}

static protocol_connection_t *test_create_connection(const int fd)
{
    protocol_connection_t *connection = calloc(1, sizeof(protocol_connection_t));

    if (!connection)
        cr_assert_fail();
    connection->fd = fd;
    return connection;
}

static protocol_payload_t* test_create_payload(
    const int fd,
    const char *message)
{
    protocol_payload_t *payload = calloc(1, sizeof(protocol_payload_t));

    if (!payload)
        cr_assert_fail();
    payload->fd = fd;
    strncpy(payload->message, message, sizeof(payload->message));
    return payload;
}

static void test_destroy_server(zappy_server_t *server)
{
    free(server->socket);
    free(server);
}

Test(payload, handle_new_connection)
{
    zappy_server_t *server = test_create_server();

    protocol_connection_t *connection = test_create_connection(1);
    TAILQ_INSERT_TAIL(&server->socket->new_connections, connection, entries);

    cr_redirect_stdout();
    handle_payload(server);
    fflush(stdout);
    cr_assert_stdout_eq_str(
        "New connection from 1\n"
        "To client 1: WELCOME\n");

    cr_assert(TAILQ_EMPTY(&server->socket->new_connections));

    test_destroy_server(server);
}

Test(payload, handle_lost_connection)
{
    zappy_server_t *server = test_create_server();
    protocol_connection_t *connection = test_create_connection(1);
    TAILQ_INSERT_TAIL(&server->socket->lost_connections, connection, entries);

    cr_redirect_stdout();
    handle_payload(server);
    fflush(stdout);
    cr_assert_stdout_eq_str("Lost connection from 1\n");

    cr_assert(TAILQ_EMPTY(&server->socket->lost_connections));

    test_destroy_server(server);
}

Test(payload, handle_ai_connection)
{
    zappy_server_t *server = test_create_server();
    team_t team = {.name = "Team1", .slots = server->clients_nb};
    TAILQ_INSERT_TAIL(&server->teams, &team, entries);

    protocol_connection_t *new_connection = test_create_connection(1);
    TAILQ_INSERT_TAIL(&server->socket->new_connections, new_connection, entries);

    protocol_payload_t *payload = test_create_payload(1, "Team1");
    TAILQ_INSERT_TAIL(&server->socket->payloads, payload, entries);

    cr_redirect_stdout();
    handle_payload(server);

    protocol_connection_t *lost_connection = test_create_connection(1);
    TAILQ_INSERT_TAIL(&server->socket->lost_connections, lost_connection, entries);

    handle_payload(server);
    fflush(stdout);
    cr_assert_stdout_eq_str(
        "New connection from 1\n"
        "To client 1: WELCOME\n"
        "New AI connected\n"
        "To client 1: 5\n"
        "To client 1: 3 3\n"
        "Lost connection from 1\n"
        "AI disconnected\n");

    test_destroy_server(server);
}

Test(payload, handle_ai_connection_no_team)
{
    zappy_server_t *server = test_create_server();
    team_t team = {.name = "Team1"};
    TAILQ_INSERT_TAIL(&server->teams, &team, entries);

    protocol_connection_t *new_connection = test_create_connection(1);
    TAILQ_INSERT_TAIL(&server->socket->new_connections, new_connection, entries);

    protocol_payload_t *payload = test_create_payload(1, "Team2");
    TAILQ_INSERT_TAIL(&server->socket->payloads, payload, entries);

    cr_redirect_stdout();
    handle_payload(server);
    fflush(stdout);
    cr_assert_stdout_eq_str(
        "New connection from 1\n"
        "To client 1: WELCOME\n"
        "\033[31m[ERROR]\033[0m Team not found\n");

    test_destroy_server(server);
}

Test(payload, handle_gui_connection)
{
    zappy_server_t *server = test_create_server();
    team_t team = {.name = "Team1"};
    TAILQ_INSERT_TAIL(&server->teams, &team, entries);

    protocol_connection_t *new_connection = test_create_connection(1);
    TAILQ_INSERT_TAIL(&server->socket->new_connections, new_connection, entries);

    protocol_payload_t *payload = test_create_payload(1, "GRAPHIC");
    TAILQ_INSERT_TAIL(&server->socket->payloads, payload, entries);

    cr_redirect_stdout();
    handle_payload(server);
    fflush(stdout);
    cr_assert_stdout_eq_str(
        "New connection from 1\n"
        "To client 1: WELCOME\n"
        "New GUI connected\n"
        "To client 1: msz 3 3\n"
        "To client 1: sgt 5\n"
        "To client 1: bct 0 0 0 0 0 0 0 0 0\n"
        "To client 1: bct 0 1 0 0 0 0 0 0 0\n"
        "To client 1: bct 0 2 0 0 0 0 0 0 0\n"
        "To client 1: bct 1 0 0 0 0 0 0 0 0\n"
        "To client 1: bct 1 1 0 0 0 0 0 0 0\n"
        "To client 1: bct 1 2 0 0 0 0 0 0 0\n"
        "To client 1: bct 2 0 0 0 0 0 0 0 0\n"
        "To client 1: bct 2 1 0 0 0 0 0 0 0\n"
        "To client 1: bct 2 2 0 0 0 0 0 0 0\n"
        "To client 1: tna Team1\n");

    test_destroy_server(server);
}

Test(payload, handle_ai_command)
{
    zappy_server_t *server = test_create_server();
    clock_gettime(CLOCK_REALTIME, &server->last_update);
    server->last_update.tv_sec -= 10;
    team_t team = {.name = "Team1", .slots = server->clients_nb};
    TAILQ_INSERT_TAIL(&server->teams, &team, entries);

    protocol_connection_t *new_connection = test_create_connection(1);
    TAILQ_INSERT_TAIL(&server->socket->new_connections, new_connection, entries);

    protocol_payload_t *payload = test_create_payload(1, "Team1");
    TAILQ_INSERT_TAIL(&server->socket->payloads, payload, entries);

    protocol_payload_t *command = test_create_payload(1, "Forward");
    TAILQ_INSERT_TAIL(&server->socket->payloads, command, entries);

    cr_redirect_stdout();
    handle_payload(server);
    update_game(server);
    handle_payload(server);
    fflush(stdout);
    cr_assert_stdout_eq_str(
        "New connection from 1\n"
        "To client 1: WELCOME\n"
        "New AI connected\n"
        "To client 1: 5\n"
        "To client 1: 3 3\n"
        "AI 1: Forward\n"
        "To client 1: ok\n");

    test_destroy_server(server);
}

Test(payload, handle_ai_command_unknown)
{
    zappy_server_t *server = test_create_server();
    clock_gettime(CLOCK_REALTIME, &server->last_update);
    server->last_update.tv_sec -= 10;
    team_t team = {.name = "Team1", .slots = server->clients_nb};
    TAILQ_INSERT_TAIL(&server->teams, &team, entries);

    protocol_connection_t *new_connection = test_create_connection(1);
    TAILQ_INSERT_TAIL(&server->socket->new_connections, new_connection, entries);

    protocol_payload_t *payload = test_create_payload(1, "Team1");
    TAILQ_INSERT_TAIL(&server->socket->payloads, payload, entries);

    protocol_payload_t *command = test_create_payload(1, "Unknown");
    TAILQ_INSERT_TAIL(&server->socket->payloads, command, entries);

    cr_redirect_stdout();
    handle_payload(server);
    update_game(server);
    handle_payload(server);
    fflush(stdout);
    cr_assert_stdout_eq_str(
        "New connection from 1\n"
        "To client 1: WELCOME\n"
        "New AI connected\n"
        "To client 1: 5\n"
        "To client 1: 3 3\n"
        "AI 1: Unknown\n"
        "To client 1: ko\n");

    test_destroy_server(server);
}

Test(payload, handle_gui_command)
{
    zappy_server_t *server = test_create_server();
    protocol_connection_t *new_connection = test_create_connection(1);
    TAILQ_INSERT_TAIL(&server->socket->new_connections, new_connection, entries);

    protocol_payload_t *payload = test_create_payload(1, "GRAPHIC");
    TAILQ_INSERT_TAIL(&server->socket->payloads, payload, entries);

    protocol_payload_t *command = test_create_payload(1, "msz");
    TAILQ_INSERT_TAIL(&server->socket->payloads, command, entries);

    cr_redirect_stdout();
    handle_payload(server);
    fflush(stdout);
    cr_assert_stdout_eq_str(
        "New connection from 1\n"
        "To client 1: WELCOME\n"
        "New GUI connected\n"
        "To client 1: msz 3 3\n"
        "To client 1: sgt 5\n"
        "To client 1: bct 0 0 0 0 0 0 0 0 0\n"
        "To client 1: bct 0 1 0 0 0 0 0 0 0\n"
        "To client 1: bct 0 2 0 0 0 0 0 0 0\n"
        "To client 1: bct 1 0 0 0 0 0 0 0 0\n"
        "To client 1: bct 1 1 0 0 0 0 0 0 0\n"
        "To client 1: bct 1 2 0 0 0 0 0 0 0\n"
        "To client 1: bct 2 0 0 0 0 0 0 0 0\n"
        "To client 1: bct 2 1 0 0 0 0 0 0 0\n"
        "To client 1: bct 2 2 0 0 0 0 0 0 0\n"
        "GUI 1: msz\n"
        "To client 1: msz 3 3\n");

    test_destroy_server(server);
}

Test(payload, handle_gui_command_unknown)
{
    zappy_server_t *server = test_create_server();
    protocol_connection_t *new_connection = test_create_connection(1);
    TAILQ_INSERT_TAIL(&server->socket->new_connections, new_connection, entries);

    protocol_payload_t *payload = test_create_payload(1, "GRAPHIC");
    TAILQ_INSERT_TAIL(&server->socket->payloads, payload, entries);

    protocol_payload_t *command = test_create_payload(1, "Unknown");
    TAILQ_INSERT_TAIL(&server->socket->payloads, command, entries);

    cr_redirect_stdout();
    handle_payload(server);
    fflush(stdout);
    cr_assert_stdout_eq_str(
        "New connection from 1\n"
        "To client 1: WELCOME\n"
        "New GUI connected\n"
        "To client 1: msz 3 3\n"
        "To client 1: sgt 5\n"
        "To client 1: bct 0 0 0 0 0 0 0 0 0\n"
        "To client 1: bct 0 1 0 0 0 0 0 0 0\n"
        "To client 1: bct 0 2 0 0 0 0 0 0 0\n"
        "To client 1: bct 1 0 0 0 0 0 0 0 0\n"
        "To client 1: bct 1 1 0 0 0 0 0 0 0\n"
        "To client 1: bct 1 2 0 0 0 0 0 0 0\n"
        "To client 1: bct 2 0 0 0 0 0 0 0 0\n"
        "To client 1: bct 2 1 0 0 0 0 0 0 0\n"
        "To client 1: bct 2 2 0 0 0 0 0 0 0\n"
        "GUI 1: Unknown\n"
        "To client 1: suc\n");

    test_destroy_server(server);
}

Test(payload, handle_many_ai)
{
    zappy_server_t *server = test_create_server();
    clock_gettime(CLOCK_REALTIME, &server->last_update);
    server->last_update.tv_sec -= 10;
    team_t team = {.name = "Team1", .slots = server->clients_nb};
    TAILQ_INSERT_TAIL(&server->teams, &team, entries);

    for (int i = 1; i <= 5; ++i) {
        protocol_connection_t *new_connection = test_create_connection(i);
        TAILQ_INSERT_TAIL(&server->socket->new_connections, new_connection, entries);

        protocol_payload_t *payload = test_create_payload(i, "Team1");
        TAILQ_INSERT_TAIL(&server->socket->payloads, payload, entries);

        protocol_payload_t *command = test_create_payload(i, "Forward");
        TAILQ_INSERT_TAIL(&server->socket->payloads, command, entries);
    }

    cr_redirect_stdout();
    handle_payload(server);
    update_game(server);
    handle_payload(server);
    fflush(stdout);
    cr_assert_stdout_eq_str(
        "New connection from 1\n"
        "To client 1: WELCOME\n"
        "New connection from 2\n"
        "To client 2: WELCOME\n"
        "New connection from 3\n"
        "To client 3: WELCOME\n"
        "New connection from 4\n"
        "To client 4: WELCOME\n"
        "New connection from 5\n"
        "To client 5: WELCOME\n"
        "New AI connected\n"
        "To client 1: 5\n"
        "To client 1: 3 3\n"
        "AI 1: Forward\n"
        "New AI connected\n"
        "To client 2: 4\n"
        "To client 2: 3 3\n"
        "AI 2: Forward\n"
        "New AI connected\n"
        "To client 3: 3\n"
        "To client 3: 3 3\n"
        "AI 3: Forward\n"
        "New AI connected\n"
        "To client 4: 2\n"
        "To client 4: 3 3\n"
        "AI 4: Forward\n"
        "New AI connected\n"
        "To client 5: 1\n"
        "To client 5: 3 3\n"
        "AI 5: Forward\n"
        "To client 1: ok\n"
        "To client 2: ok\n"
        "To client 3: ok\n"
        "To client 4: ok\n"
        "To client 5: ok\n");

    test_destroy_server(server);
}

Test(payload, handle_many_gui)
{
    zappy_server_t *server = test_create_server();
    team_t team = {.name = "Team1"};
    TAILQ_INSERT_TAIL(&server->teams, &team, entries);

    for (int i = 1; i <= 3; ++i) {
        protocol_connection_t *new_connection = test_create_connection(i);
        TAILQ_INSERT_TAIL(&server->socket->new_connections, new_connection, entries);

        protocol_payload_t *payload = test_create_payload(i, "GRAPHIC");
        TAILQ_INSERT_TAIL(&server->socket->payloads, payload, entries);

        protocol_payload_t *command = test_create_payload(i, "msz");
        TAILQ_INSERT_TAIL(&server->socket->payloads, command, entries);
    }

    cr_redirect_stdout();
    handle_payload(server);
    fflush(stdout);
    cr_assert_stdout_eq_str(
        "New connection from 1\n"
        "To client 1: WELCOME\n"
        "New connection from 2\n"
        "To client 2: WELCOME\n"
        "New connection from 3\n"
        "To client 3: WELCOME\n"
        "New GUI connected\n"
        "To client 1: msz 3 3\n"
        "To client 1: sgt 5\n"
        "To client 1: bct 0 0 0 0 0 0 0 0 0\n"
        "To client 1: bct 0 1 0 0 0 0 0 0 0\n"
        "To client 1: bct 0 2 0 0 0 0 0 0 0\n"
        "To client 1: bct 1 0 0 0 0 0 0 0 0\n"
        "To client 1: bct 1 1 0 0 0 0 0 0 0\n"
        "To client 1: bct 1 2 0 0 0 0 0 0 0\n"
        "To client 1: bct 2 0 0 0 0 0 0 0 0\n"
        "To client 1: bct 2 1 0 0 0 0 0 0 0\n"
        "To client 1: bct 2 2 0 0 0 0 0 0 0\n"
        "To client 1: tna Team1\n"
        "GUI 1: msz\n"
        "To client 1: msz 3 3\n"
        "New GUI connected\n"
        "To client 2: msz 3 3\n"
        "To client 2: sgt 5\n"
        "To client 2: bct 0 0 0 0 0 0 0 0 0\n"
        "To client 2: bct 0 1 0 0 0 0 0 0 0\n"
        "To client 2: bct 0 2 0 0 0 0 0 0 0\n"
        "To client 2: bct 1 0 0 0 0 0 0 0 0\n"
        "To client 2: bct 1 1 0 0 0 0 0 0 0\n"
        "To client 2: bct 1 2 0 0 0 0 0 0 0\n"
        "To client 2: bct 2 0 0 0 0 0 0 0 0\n"
        "To client 2: bct 2 1 0 0 0 0 0 0 0\n"
        "To client 2: bct 2 2 0 0 0 0 0 0 0\n"
        "To client 2: tna Team1\n"
        "GUI 2: msz\n"
        "To client 2: msz 3 3\n"
        "New GUI connected\n"
        "To client 3: msz 3 3\n"
        "To client 3: sgt 5\n"
        "To client 3: bct 0 0 0 0 0 0 0 0 0\n"
        "To client 3: bct 0 1 0 0 0 0 0 0 0\n"
        "To client 3: bct 0 2 0 0 0 0 0 0 0\n"
        "To client 3: bct 1 0 0 0 0 0 0 0 0\n"
        "To client 3: bct 1 1 0 0 0 0 0 0 0\n"
        "To client 3: bct 1 2 0 0 0 0 0 0 0\n"
        "To client 3: bct 2 0 0 0 0 0 0 0 0\n"
        "To client 3: bct 2 1 0 0 0 0 0 0 0\n"
        "To client 3: bct 2 2 0 0 0 0 0 0 0\n"
        "To client 3: tna Team1\n"
        "GUI 3: msz\n"
        "To client 3: msz 3 3\n");

    test_destroy_server(server);
}
