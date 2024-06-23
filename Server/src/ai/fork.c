/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** fork
*/

#include "server/ai_header.h"
#include "server/gui.h"

bool can_fork(
    zappy_server_t *server,
    ai_t *ai,
    UNUSED const char *message)
{
    pfk(server, ai);
    return true;
}

void exec_fork(
    zappy_server_t *server,
    ai_t *ai,
    UNUSED const char *message)
{
    enw(server, ai, egg_spawn(server, ai));
    server_send(server, ai->fd, "ok");
}
