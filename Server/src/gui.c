/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** gui
*/

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#include "server/gui.h"

void create_gui(
    zappy_server_t *server,
    const protocol_payload_t *payload)
{
    gui_t *gui = calloc(1, sizeof(gui_t));
    ai_t *ai;

    if (!gui)
        return;
    gui->fd = payload->fd;
    TAILQ_INSERT_TAIL(&server->guis, gui, entries);
    verbose(server, "New GUI connected\n");
    msz(server, payload->fd, "");
    sgt(server, payload->fd, "");
    mct(server, payload->fd, "");
    tna(server, payload->fd, "");
    TAILQ_FOREACH(ai, &server->ais, entries)
        if (ai->state != DEAD)
            pnw(server, ai);
}

void handle_event_gui(
    zappy_server_t *server,
    const protocol_payload_t *payload)
{
    uint8_t len;

    for (uint8_t i = 0; gui_cmds[i].func; ++i) {
        len = strlen(gui_cmds[i].cmd);
        if (!strncmp(payload->message, gui_cmds[i].cmd, len)) {
            gui_cmds[i].func(server, payload->fd, payload->message + len + 1);
            return;
        }
    }
    suc(server, payload->fd);
}

void gui_send_to_all(
    const zappy_server_t *server,
    const char *message,
    ...)
{
    char formatted_message[DATA_SIZE] = {0};
    const gui_t *gui;
    va_list args;

    va_start(args, message);
    vsnprintf(formatted_message, DATA_SIZE, message, args);
    va_end(args);
    TAILQ_FOREACH(gui, &server->guis, entries)
        protocol_server_send(server->socket, gui->fd, formatted_message);
}
