/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** egg
*/

#include <stdlib.h>

#include "server/ai_header.h"

uint16_t egg_spawn(
    zappy_server_t *server,
    const ai_t *ai)
{
    egg_t *egg = calloc(1, sizeof(egg_t));

    if (!egg)
        return 0;
    *egg = (egg_t){ .id = server->egg_id++, .pos = ai->pos, .team = ai->team };
    TAILQ_INSERT_TAIL(&server->eggs, egg, entries);
    return egg->id;
}

egg_t *egg_pop_by_team(
    zappy_server_t *server,
    const team_t *team)
{
    egg_t *egg;

    TAILQ_FOREACH(egg, &server->eggs, entries)
        if (egg->team == team) {
            TAILQ_REMOVE(&server->eggs, egg, entries);
            return egg;
        }
    return NULL;
}
