#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "server/gui.h"

Test(sbp, check_if_sbp_is_correct)
{
    zappy_server_t server = {};

    cr_redirect_stdout();
    sbp(&server, 0);
    cr_assert_stdout_eq_str("To client 0: sbp\n");
}
