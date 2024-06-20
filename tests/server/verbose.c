#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "server.h"

Test(verbose, verbose_true, .init = cr_redirect_stdout)
{
    zappy_server_t server = {0};

    server.verbose = true;
    verbose(&server, "Hello World!");
    fflush(stdout);
    cr_assert_stdout_eq_str("Hello World!");
}

Test(verbose, verbose_false, .init = cr_redirect_stdout)
{
    zappy_server_t server = {0};

    server.verbose = false;
    verbose(&server, "Hello World!");
    fflush(stdout);
    cr_assert_stdout_eq_str("");
}
