/*
** EPITECH PROJECT, 2024
** Server
** File description:
** main
*/

#include <stdio.h>
#include <unistd.h>

#include "server/flags.h"

static int usage(void)
{
    return puts("USAGE: ./zappy_server -p port -x width -y height"
        " -n name1 name2 ... -c clientsNb -f freq [-v | --verbose]"
        "\n\tport\t\tis the port number"
        "\n\twidth\t\tis the width of the world"
        "\n\theight\t\tis the height of the world"
        "\n\tnameX\t\tis the name of the team X"
        "\n\tclientsNb\tis the number of authorized clients per team"
        "\n\tfreq\t\tis the reciprocal of time unit for execution of actions"
        ) > 0 ? true : false;
}

static bool handle_opt(
    zappy_server_t *server,
    const optargs_t *optargs)
{
    for (size_t i = 0; i < sizeof(opt_cmds) / sizeof(opt_cmds[0]); ++i)
        if (opt_cmds[i].flag == optargs->opt) {
            opt_cmds[i].func(server, optargs);
            return true;
        }
    return false;
}

int main(const int ac, char **av)
{
    zappy_server_t server = {0};

    server_init(&server);
    for (int opt = getopt(ac, av, "p:x:y:n:c:f:v"); opt != -1;
        opt = getopt(ac, av, "p:x:y:n:c:f:v"))
        if (!handle_opt(&server, &(optargs_t){ac, av, opt, optarg})) {
            usage();
            return 84;
        }
    return zappy_server(&server) ? 0 : 84;
}
