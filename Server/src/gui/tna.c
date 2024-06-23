/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** tna
*/

#include "server.h"

// Response to "tna\n"
void tna(
    zappy_server_t *server,
    const int interlocutor,
    UNUSED const char *message)
{
    const team_t *team;

    TAILQ_FOREACH(team, &server->teams, entries)
        server_send(server, interlocutor, "tna %s",
            team->name);
}
