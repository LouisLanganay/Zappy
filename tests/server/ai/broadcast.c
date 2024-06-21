#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "server/ai_header.h"

Test(broadcast, check_bad_argument)
{
    zappy_server_t server = {};
    ai_t ai1 = {.fd = 1};

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);
    cr_redirect_stdout();
    broadcast_text(&server, &ai1, "");
    cr_assert_stdout_eq_str("To client 1: ko\n");
}

Test(broadcast, check_player_alone_message)
{
    zappy_server_t server = {};
    ai_t ai1 = {.fd = 1};

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);
    cr_redirect_stdout();
    broadcast_text(&server, &ai1, " Hello World!");
    cr_assert_stdout_eq_str("To client 1: ok\n");
}

Test(broadcast, check_message_reception)
{
    zappy_server_t server = {.height = 11, .width = 10};
    vector2_t sender_pos = {9, 2};
    vector2_t reciever_pos = {2, 5};
    ai_t sender = {.fd = 1, .pos = sender_pos, .orientation = NORTH};
    ai_t reciever = {.fd = 2, .pos = reciever_pos, .orientation = EAST};

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &sender, entries);
    TAILQ_INSERT_TAIL(&server.ais, &reciever, entries);
    cr_redirect_stdout();
    broadcast_text(&server, &sender, " Hello World!");
    cr_assert_stdout_eq_str("To client 2: message 4, Hello World!\n"
                            "To client 1: ok\n");
}

Test(broadcast, check_message_reception_on_the_same_tile)
{
    zappy_server_t server = {.height = 11, .width = 10};
    ai_t sender = {.fd = 1, .pos = {0, 0}, .orientation = NORTH};
    ai_t reciever = {.fd = 2, .pos = {0, 0}, .orientation = WEST};

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &sender, entries);
    TAILQ_INSERT_TAIL(&server.ais, &reciever, entries);
    cr_redirect_stdout();
    broadcast_text(&server, &sender, " Hello World!");
    cr_assert_stdout_eq_str("To client 2: message 0, Hello World!\n"
                            "To client 1: ok\n");
}
