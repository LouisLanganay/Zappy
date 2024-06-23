#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "server/gui.h"

Test(pic, check_if_pic_is_correct)
{
    zappy_server_t server = {};
    ai_t ai[4] = {{.id = 1, .pos = {2, 4}, .level = 3}, {.id = 2}, {.id = 3}, {.id = 4}};
    gui_t gui1 = {.fd = 1};
    gui_t gui2 = {.fd = 2};
    gui_t gui3 = {.fd = 3};

    TAILQ_INIT(&server.guis);
    TAILQ_INSERT_TAIL(&server.guis, &gui1, entries);
    TAILQ_INSERT_TAIL(&server.guis, &gui2, entries);
    TAILQ_INSERT_TAIL(&server.guis, &gui3, entries);

    cr_redirect_stdout();
    const ai_t *ai_pointer[] = { &ai[0], &ai[1], &ai[2], &ai[3], NULL };
    pic(&server, ai_pointer);
    cr_assert_stdout_eq_str(
        "To client 1: pic 2 4 3 1 2 3 4\n"
        "To client 2: pic 2 4 3 1 2 3 4\n"
        "To client 3: pic 2 4 3 1 2 3 4\n");
}
