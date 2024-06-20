#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "server/gui.h"

Test(sgt, check_if_sgt_is_correct)
{
    zappy_server_t server = {.freq = 10};

    cr_redirect_stdout();
    sgt(&server, 0, "");
    cr_assert_stdout_eq_str("To client 0: sgt 10\n");
}
