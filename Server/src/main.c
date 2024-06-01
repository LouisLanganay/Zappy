/*
** EPITECH PROJECT, 2024
** Server
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "server.h"

static int usage(void)
{
    return puts("USAGE: ./zappy_server -p port -x width -y height"
        "-n name1 name2 ... -c clientsNb -f freq [-v | --verbose]"
        "\n\tport\t\tis the port number"
        "\n\twidth\t\tis the width of the world"
        "\n\theight\t\tis the height of the world"
        "\n\tnameX\t\tis the name of the team X"
        "\n\tclientsNb\tis the number of authorized clients per team"
        "\n\tfreq\t\tis the reciprocal of time unit for execution of actions"
        ) > 0 ? true : false;
}

int main(const int ac, char **av)
{
    zappy_server_t server = {0};

    server_init(&server);
    for (int opt = getopt(ac, av, "p:x:y:n:c:f:v"); opt != -1;
        opt = getopt(ac, av, "p:x:y:n:c:f:v"))
        switch (opt) {
        case 'p':
            server.port = atoi(optarg);
            break;
        case 'x':
            server.width = atoi(optarg);
            break;
        case 'y':
            server.height = atoi(optarg);
            break;
        case 'n':
            for (int i = optind - 1; i < ac && av[i][0] != '-'; ++i) {
                team_t *team = calloc(1, sizeof(team_t));
                if (!team)
                    return 84;
                team->id = server.teams.tqh_last ? ((team_t *)server.teams.tqh_last)->id + 1 : 0;
                strncpy(team->name, av[i], 64);
                TAILQ_INSERT_TAIL(&server.teams, team, entries);
            }
            break;
        case 'c':
            server.clients_nb = atoi(optarg);
            break;
        case 'f':
            server.freq = atoi(optarg);
            break;
        case 'v':
            server.verbose = true;
            break;
        default:
            usage();
            return 84;
        }
    return zappy_server(&server) ? 0 : 84;
}
