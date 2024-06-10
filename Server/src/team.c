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

uint16_t team_get_empty_slots(
    const zappy_server_t *server,
    const team_t *team)
{
    uint16_t used_slots = 0;
    ai_t *ai;

    TAILQ_FOREACH(ai, &server->ais, entries)
        if (ai->team == team)
            used_slots++;
    return server->clients_nb - used_slots;
}
