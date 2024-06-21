#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "server/ai_header.h"

Test(death, check_if_message_is_sent_to_ai)
{
    zappy_server_t server = {};
    ai_t ai1 = {.fd = 1};

    TAILQ_INIT(&server.ais);
    TAILQ_INSERT_TAIL(&server.ais, &ai1, entries);
    cr_redirect_stdout();
    death(&server, &ai1, "");
    cr_assert_stdout_eq_str("To client 1: dead\n");
}
