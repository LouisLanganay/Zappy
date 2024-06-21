#include <arpa/inet.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "protocol/server.h"

Test(protocol_client_create, create_new_socket_for_client)
{
    protocol_server_t *server = protocol_server_create(5000);
    protocol_client_t *client = protocol_client_create("127.0.0.1", 5000);

    cr_assert_not_null(server);
    cr_assert_not_null(client);
    cr_assert_gt(client->network_data.sockfd, 0);
    cr_assert_eq(client->network_data.server_addr.sin_port, htons(5000));
    cr_assert_eq(client->network_data.server_addr.sin_addr.s_addr, inet_addr("127.0.0.1"));
    cr_assert_eq(client->network_data.server_addr.sin_family, AF_INET);
    cr_assert(protocol_client_is_connected(client));

    protocol_client_close(client);
    protocol_server_close(server);
}

Test(protocol_client_create, failed_to_connect)
{
    cr_redirect_stderr();
    protocol_client_t *client = protocol_client_create("127.0.0.1", 5001);
    cr_assert_null(client);
    cr_assert_stderr_eq_str("\033[31m[ERROR]\033[0m Connection refused\n");
}

Test(protocol_client_close, failed_close)
{
    protocol_client_t *client = calloc(1, sizeof(protocol_client_t));

    cr_assert_not_null(client);
    client->network_data.sockfd = -1;

    cr_redirect_stderr();
    protocol_client_close(client);
    cr_assert_stderr_eq_str("\033[31m[ERROR]\033[0m Bad file descriptor\n");
}

Test(protocol_client_listen, client_listen)
{
    protocol_server_t *server = protocol_server_create(5002);
    protocol_client_t *client = protocol_client_create("127.0.0.1", 5002);

    cr_assert_not_null(server);
    cr_assert_not_null(client);

    cr_assert_null(protocol_server_listen(server));
    cr_assert_not(TAILQ_EMPTY(&server->new_connections));

    protocol_server_send(server, TAILQ_FIRST(&server->new_connections)->fd, "Hello World!");
    cr_assert_not_null(protocol_client_listen(client));
    cr_assert_not(TAILQ_EMPTY(&client->payloads));
    cr_assert_str_eq(TAILQ_FIRST(&client->payloads)->message, "Hello World!");

    protocol_client_close(client);
    protocol_server_close(server);
}
