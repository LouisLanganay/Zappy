#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "server/gui.h"

Test(msz, check_if_msz_is_correct)
{
    zappy_server_t server = {.width = 10, .height = 10};

    cr_redirect_stdout();
    msz(&server, 0, NULL);
    cr_assert_stdout_eq_str("To client 0: msz 10 10\n");
}
