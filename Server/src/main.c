/*
** EPITECH PROJECT, 2024
** Server
** File description:
** main
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "server/gui.h"
#include "server.h"

bool display_server(const zappy_server_t *server)
{
    return printf(
        "===================Zappy Server==================="
        "\nport = %hu"
        "\nwidth = %hu"
        "\nheight = %hu"
        "\nclients_nb = %hu"
        "\nfreq = %hu"
        "\nTeams [%hu]:"
        // teams name
        "\nverbose = %d"
        "\n==================================================\n",
        server->port,
        server->width,
        server->height,
        server->clients_nb,
        server->freq,
        server->teams.tqh_last ? ((team_t *)server->teams.tqh_last)->id + 1 : 0,
        server->verbose) > 0 ? true : false;
}

int usage(void)
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

bool zappy_server(zappy_server_t *server)
{
    if (!server || server->port < 1024
        || server->width <= 0 || server->height <= 0)
        return false;
    display_server(server);

    server->socket = protocol_server_create(server->port);
    if (!server->socket)
        return false;

    while (protocol_server_is_open()) {
        protocol_server_listen(server->socket);
        while (!TAILQ_EMPTY(&server->socket->payloads)) {
            protocol_payload_t *payload = TAILQ_FIRST(&server->socket->payloads);
            TAILQ_REMOVE(&server->socket->payloads, payload, entries);
            switch (payload->packet.type) {
            case EVT_MSZ:
            case EVT_BCT:
            case EVT_MCT:
            case EVT_TNA:
            case EVT_PPO:
            case EVT_PLV:
            case EVT_PIN:
                gui_cmds[payload->packet.type].func(server, payload);
                break;
            default:
                suc(server, payload);
                break;
            }
            free(payload);
        }
    }

    return true;
}

int main(const int ac, char **av)
{
    zappy_server_t server = { .port = 4242, .width = 10, .height = 10 };

    TAILQ_INIT(&server.ais);
    TAILQ_INIT(&server.teams);
    TAILQ_INIT(&server.guis);

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
            team_t *team = calloc(1, sizeof(team_t));
            if (!team)
                return 84;
            team->id = server.teams.tqh_last ? ((team_t *)server.teams.tqh_last)->id + 1 : 0;
            strncpy(team->name, optarg, 64);
            TAILQ_INSERT_TAIL(&server.teams, team, entries);
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
