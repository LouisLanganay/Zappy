#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "server.h"

Test(gui_send_to_all, check_if_message_is_sent_to_all)
{
    zappy_server_t server = {};
    gui_t gui1 = {.fd = 1};
    gui_t gui2 = {.fd = 2};
    gui_t gui3 = {.fd = 3};

    TAILQ_INIT(&server.guis);
    TAILQ_INSERT_TAIL(&server.guis, &gui1, entries);
    TAILQ_INSERT_TAIL(&server.guis, &gui2, entries);
    TAILQ_INSERT_TAIL(&server.guis, &gui3, entries);

    cr_redirect_stdout();
    gui_send_to_all(&server, "Hello World!");
    cr_assert_stdout_eq_str(
        "To client 1: Hello World!\n"
        "To client 2: Hello World!\n"
        "To client 3: Hello World!\n");
}

Test(gui_send_to_all, check_if_message_is_sent_to_all_with_args)
{
    zappy_server_t server = {};
    gui_t gui1 = {.fd = 1};
    gui_t gui2 = {.fd = 2};
    gui_t gui3 = {.fd = 3};

    TAILQ_INIT(&server.guis);
    TAILQ_INSERT_TAIL(&server.guis, &gui1, entries);
    TAILQ_INSERT_TAIL(&server.guis, &gui2, entries);
    TAILQ_INSERT_TAIL(&server.guis, &gui3, entries);

    cr_redirect_stdout();
    gui_send_to_all(&server, "Hello %s!", "World");
    cr_assert_stdout_eq_str(
        "To client 1: Hello World!\n"
        "To client 2: Hello World!\n"
        "To client 3: Hello World!\n");
}
