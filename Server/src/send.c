/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** send
*/

#include <stdarg.h>
#include <stdio.h>

#include "server/ai_header.h"

static void clear_ai(
    zappy_server_t *server,
    const int interlocutor)
{
    ai_t *next;

    for (const ai_t *ai = TAILQ_FIRST(&server->ais); ai; ai = next) {
        next = TAILQ_NEXT(ai, entries);
        if (ai->fd != interlocutor)
            continue;
        TAILQ_REMOVE(&server->ais, ai, entries);
    }
}

static void clear_gui(
    zappy_server_t *server,
    const int interlocutor)
{
    gui_t *next;

    for (const gui_t *gui = TAILQ_FIRST(&server->guis); gui; gui = next) {
        next = TAILQ_NEXT(gui, entries);
        if (gui->fd != interlocutor)
            continue;
        TAILQ_REMOVE(&server->guis, gui, entries);
    }
}

void server_send(
    zappy_server_t *server,
    const int interlocutor,
    const char *format,
    ...)
{
    char message[DATA_SIZE] = {0};
    va_list args;

    if (server->send_as_failed)
        return;
    va_start(args, format);
    vsnprintf(message, sizeof(message) - 1, format, args);
    va_end(args);
    if (protocol_server_send(server->socket, interlocutor, message))
        return;
    server->send_as_failed = true;
    clear_ai(server, interlocutor);
    clear_gui(server, interlocutor);
}
