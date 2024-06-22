/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** fork
*/

#include "server/ai_header.h"
#include "server/gui.h"

void exec_fork(
    zappy_server_t *server,
    ai_t *ai,
    UNUSED const char *message)
{
    enw(server, ai, egg_spawn(server, ai));
}
