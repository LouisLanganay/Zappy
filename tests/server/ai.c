#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "server.h"

Test(ai_send_to_all, check_if_message_is_sent_to_all, .init = cr_redirect_stdout)
{
    zappy_server_t server = {};
    ai_t ai1 = {.fd = 1};
    ai_t ai2 = {.fd = 2};
    ai_t ai3 = {.fd = 3};

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);
    TAILQ_INSERT_TAIL(&server.ais, &ai2, entries);
    TAILQ_INSERT_TAIL(&server.ais, &ai3, entries);
    ai_send_to_all(&server, "Hello World!");
    cr_assert_stdout_eq_str(
        "To client 1: Hello World!\n"
        "To client 2: Hello World!\n"
        "To client 3: Hello World!\n");
}

Test(ai_get_by_id, check_if_ai_is_found)
{
    zappy_server_t server = {};
    ai_t ai1 = {.id = 1};
    ai_t ai2 = {.id = 2};
    ai_t ai3 = {.id = 3};

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);
    TAILQ_INSERT_TAIL(&server.ais, &ai2, entries);
    TAILQ_INSERT_TAIL(&server.ais, &ai3, entries);
    cr_assert_eq(ai_get_by_id(&server, 2), &ai2);
}

Test(ai_get_by_id, check_if_ai_is_not_found)
{
    zappy_server_t server = {};
    ai_t ai1 = {.id = 1};
    ai_t ai2 = {.id = 2};
    ai_t ai3 = {.id = 3};

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);
    TAILQ_INSERT_TAIL(&server.ais, &ai2, entries);
    TAILQ_INSERT_TAIL(&server.ais, &ai3, entries);
    cr_assert_eq(ai_get_by_id(&server, 4), NULL);
}

Test(ai_get_by_fd, check_if_ai_is_found)
{
    zappy_server_t server = {};
    ai_t ai1 = {.fd = 1};
    ai_t ai2 = {.fd = 2};
    ai_t ai3 = {.fd = 3};

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);
    TAILQ_INSERT_TAIL(&server.ais, &ai2, entries);
    TAILQ_INSERT_TAIL(&server.ais, &ai3, entries);
    cr_assert_eq(ai_get_by_fd(&server, 2), &ai2);
}

Test(ai_get_by_fd, check_if_ai_is_not_found)
{
    zappy_server_t server = {};
    ai_t ai1 = {.fd = 1};
    ai_t ai2 = {.fd = 2};
    ai_t ai3 = {.fd = 3};

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);
    TAILQ_INSERT_TAIL(&server.ais, &ai2, entries);
    TAILQ_INSERT_TAIL(&server.ais, &ai3, entries);
    cr_assert_eq(ai_get_by_fd(&server, 4), NULL);
}

Test(ai_get_nb_by_pos, check_if_nb_is_found)
{
    zappy_server_t server = {};
    ai_t ai1 = {.pos = {1, 1}};
    ai_t ai2 = {.pos = {1, 1}};
    ai_t ai3 = {.pos = {1, 1}};

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);
    TAILQ_INSERT_TAIL(&server.ais, &ai2, entries);
    TAILQ_INSERT_TAIL(&server.ais, &ai3, entries);
    cr_assert_eq(ai_get_nb_by_pos(&server, &ai1.pos), 3);
}

Test(ai_get_nb_by_pos, check_if_nb_is_not_found)
{
    zappy_server_t server = {};
    ai_t ai1 = {.pos = {2, 1}};
    ai_t ai2 = {.pos = {1, 2}};
    ai_t ai3 = {.pos = {2, 2}};

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);
    TAILQ_INSERT_TAIL(&server.ais, &ai2, entries);
    TAILQ_INSERT_TAIL(&server.ais, &ai3, entries);
    cr_assert_eq(ai_get_nb_by_pos(&server, &(vector2_t){1, 1}), 0);
}
