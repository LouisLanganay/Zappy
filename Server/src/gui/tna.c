/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** tna
*/

#include "server.h"

void tna(
    zappy_server_t *server,
    const int interlocutor,
    UNUSED const char *message)
{
    const team_t *team;

    TAILQ_FOREACH(team, &server->teams, entries)
        protocol_server_send(server->socket, interlocutor, "tna %s",
            team->name);
}
