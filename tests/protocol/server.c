#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "protocol/server.h"

#include <signal.h>
#include <unistd.h>

Test(protocol_server_create, create_new_socket_for_server) {
    protocol_server_t *server = protocol_server_create(4000);

    cr_assert_not_null(server);
    cr_assert_gt(server->network_data.sockfd, 0);
    cr_assert_eq(server->network_data.server_addr.sin_port, htons(4000));
    cr_assert_eq(server->network_data.server_addr.sin_addr.s_addr, INADDR_ANY);
    cr_assert_eq(server->network_data.server_addr.sin_family, AF_INET);

    for (int i = 0; i < FD_SETSIZE; i++)
        if (i == server->network_data.sockfd) {
            cr_assert(FD_ISSET(i, &server->master_read_fds));
            cr_assert(FD_ISSET(i, &server->master_write_fds));
        } else {
            cr_assert_not(FD_ISSET(i, &server->master_read_fds));
            cr_assert_not(FD_ISSET(i, &server->master_write_fds));
        }

    cr_assert(TAILQ_EMPTY(&server->clients));
    cr_assert(TAILQ_EMPTY(&server->payloads));
    cr_assert(TAILQ_EMPTY(&server->new_connections));
    cr_assert(TAILQ_EMPTY(&server->lost_connections));

    cr_assert(protocol_server_is_open());

    protocol_server_close(server);
}

Test(protocol_server_create, server_failed_address_already_in_use)
{
    protocol_server_t *server = protocol_server_create(4001);

    cr_redirect_stderr();
    protocol_server_t *server2 = protocol_server_create(4001);
    cr_assert_null(server2);
    cr_assert_stderr_eq_str("\033[31m[ERROR]\033[0m Address already in use\n");

    protocol_server_close(server);
}

Test(protocol_server_close, close_failed_due_to_invalid_server_fd)
{
    protocol_server_t *server = protocol_server_create(4002);

    server->network_data.sockfd = -1;

    cr_redirect_stderr();
    protocol_server_close(server);
    cr_assert_stderr_eq_str("\033[31m[ERROR]\033[0m Bad file descriptor\n");
}

Test(protocol_server_close, close_failed_due_to_invalid_client_fd)
{
    protocol_server_t *server = protocol_server_create(4003);
    protocol_client_t *client = calloc(1, sizeof(protocol_client_t));

    if (!client)
        cr_assert_fail();
    client->network_data.sockfd = -1;
    TAILQ_INSERT_TAIL(&server->clients, client, entries);

    cr_redirect_stderr();
    protocol_server_close(server);
    cr_assert_stderr_eq_str("\033[31m[ERROR]\033[0m Bad file descriptor\n");
}

Test(protocol_server_close, close_client)
{
    protocol_server_t *server = protocol_server_create(4004);
    protocol_client_t *client = calloc(1, sizeof(protocol_client_t));

    if (!client)
        cr_assert_fail();
    TAILQ_INSERT_TAIL(&server->clients, client, entries);

    protocol_server_close(server);
}

Test(protocol_server_is_open, close_server_with_signal)
{
    protocol_server_t *server = protocol_server_create(4005);

    cr_assert(protocol_server_is_open());

    kill(getpid(), SIGINT);
    while (protocol_server_is_open())
        usleep(100);

    cr_assert_not(protocol_server_is_open());

    protocol_server_close(server);
}

Test(protocol_server_send, send_message_to_client)
{
    protocol_server_t *server = protocol_server_create(4006);
    protocol_client_t *client = calloc(1, sizeof(protocol_client_t));

    if (!client)
        cr_assert_fail();
    client->network_data.sockfd = STDOUT_FILENO;
    TAILQ_INSERT_TAIL(&server->clients, client, entries);

    cr_redirect_stdout();
    cr_assert(protocol_server_send(server, STDOUT_FILENO, "Hello, World!"));
    cr_assert_stdout_eq_str("Hello, World!\n");

    protocol_server_close(server);
}

Test(protocol_server_send, send_message_to_invalid_client)
{
    protocol_server_t *server = protocol_server_create(4007);

    cr_redirect_stderr();
    cr_assert_not(protocol_server_send(server, -1, "Hello, World!"));
    cr_assert_stderr_eq_str("\033[31m[ERROR]\033[0m client not found\n");

    protocol_server_close(server);
}

Test(protocol_client_listen, listen_for_new_client)
{
    protocol_server_t *server = protocol_server_create(4008);
    protocol_client_t *client = protocol_client_create("127.0.0.1", 4008);

    cr_assert_null(protocol_server_listen(server));
    cr_assert_not(TAILQ_EMPTY(&server->new_connections));


    protocol_client_send(client, "Hello World!");
    cr_assert_not_null(protocol_server_listen(server));
    cr_assert_not(TAILQ_EMPTY(&server->payloads));

    protocol_payload_t *payload;
    while (!TAILQ_EMPTY(&server->payloads)) {
        payload = TAILQ_FIRST(&server->payloads);
        TAILQ_REMOVE(&server->payloads, payload, entries);
        cr_assert_str_eq(payload->message, "Hello World!");
        free(payload);
    }

    protocol_client_close(client);
    cr_assert_null(protocol_server_listen(server));
    cr_assert_not(TAILQ_EMPTY(&server->lost_connections));

    protocol_server_close(server);
}
