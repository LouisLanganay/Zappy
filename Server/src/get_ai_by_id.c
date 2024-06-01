/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** get_ai_by_id
*/

#include <string.h>

#include "server.h"

ai_t *get_ai_by_id(const zappy_server_t *server, const uint16_t id)
{
    ai_t *ai;

    TAILQ_FOREACH(ai, &server->ais, entries)
        if (ai->id == id)
            return ai;
    return NULL;
}
