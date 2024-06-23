/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** team
*/

#include <string.h>

#include "server.h"

team_t *team_get_by_name(
    const zappy_server_t *server,
    const char *name)
{
    team_t *team;

    TAILQ_FOREACH(team, &server->teams, entries)
        if (!strcmp(team->name, name))
            return team;
    return NULL;
}

team_t *team_get_by_id(
    const zappy_server_t *server,
    const uint16_t id)
{
    team_t *team;

    TAILQ_FOREACH(team, &server->teams, entries)
        if (team->id == id)
            return team;
    return NULL;
}

uint16_t team_get_nb_ai(
    const zappy_server_t *server,
    const team_t *team)
{
    ai_t *ai;
    uint16_t nb = 0;

    TAILQ_FOREACH(ai, &server->ais, entries)
        if (ai->team == team)
            ++nb;
    return nb;
}
