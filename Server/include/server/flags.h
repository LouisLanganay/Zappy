/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** flags
*/

#ifndef FLAGS_H
    #define FLAGS_H

    #include <stdlib.h>
    #include <string.h>

    #include "server.h"

typedef struct {
    int ac;
    char **av;
    int opt;
    char *optarg;
} optargs_t;

static inline void set_port(
    zappy_server_t *server,
    const optargs_t *optargs)
{
    server->port = atoi(optargs->optarg);
}

static inline void set_width(
    zappy_server_t *server,
    const optargs_t *optargs)
{
    server->width = atoi(optargs->optarg);
}

static inline void set_height(
    zappy_server_t *server,
    const optargs_t *optargs)
{
    server->height = atoi(optargs->optarg);
}

static inline void set_teams(
    zappy_server_t *server,
    const optargs_t *optargs)
{
    team_t *team;

    for (int i = optind - 1;
        i < optargs->ac && optargs->av[i][0] != '-'; ++i) {
        team = calloc(1, sizeof(team_t));
        if (!team)
            return;
        team->id = TAILQ_EMPTY(&server->teams) ? 1 :
            TAILQ_LAST(&server->teams, teamhead)->id + 1;
        strncpy(team->name, optargs->av[i], 64);
        TAILQ_INSERT_TAIL(&server->teams, team, entries);
    }
}

static inline void set_clients_nb(
    zappy_server_t *server,
    const optargs_t *optargs)
{
    server->clients_nb = atoi(optargs->optarg);
}

static inline void set_freq(
    zappy_server_t *server,
    const optargs_t *optargs)
{
    server->freq = atoi(optargs->optarg);
}

static inline void set_verbose(
    zappy_server_t *server,
    UNUSED const optargs_t *optargs)
{
    server->verbose = true;
}

static const struct {
    char flag;
    void (*func)(zappy_server_t *server, const optargs_t *optargs);
} opt_cmds[] = {
    {'p', set_port},
    {'x', set_width},
    {'y', set_height},
    {'n', set_teams},
    {'c', set_clients_nb},
    {'f', set_freq},
    {'v', set_verbose},
};

#endif //FLAGS_H
