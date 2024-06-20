#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "server/gui.h"

Test(suc, check_if_suc_is_correct)
{
    zappy_server_t server = {};

    cr_redirect_stdout();
    suc(&server, 0);
    cr_assert_stdout_eq_str("To client 0: suc\n");
}
