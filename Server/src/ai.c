/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ai
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "server/ai_header.h"
#include "server/gui.h"

static void spawn_ai(
    zappy_server_t *server,
    ai_t *ai)
{
    egg_t *egg = egg_pop_by_team(server, ai->team);

    if (!egg) {
        ai->pos = (vector2_t){rand() % server->width, rand() % server->height};
    } else {
        ebo(server, egg->id);
        ai->pos = egg->pos;
        free(egg);
    }
}

static bool connect_ai(
    zappy_server_t *server,
    const protocol_payload_t *payload,
    ai_t *ai)
{
    protocol_server_send(server->socket, payload->fd, "%i", ai->team->slots);
    if (ai->team->slots == 0) {
        protocol_server_send(server->socket, payload->fd, "ko");
        free(ai);
        return false;
    }
    ai->team->slots--;
    spawn_ai(server, ai);
    TAILQ_INSERT_TAIL(&server->ais, ai, entries);
    protocol_server_send(server->socket, payload->fd,
        "%i %i", server->width, server->height);
    return true;
}

void create_ai(
    zappy_server_t *server,
    const protocol_payload_t *payload)
{
    ai_t *ai = calloc(1, sizeof(ai_t));

    if (!ai)
        return;
    *ai = (ai_t){.id = server->ai_id++, .fd = payload->fd,
        .level = 1, .orientation = NORTH, .state = ALIVE,
        .team = team_get_by_name(server, payload->message),
        .life_span = 0, .inventory = { .food = 10 }};
    if (!ai->team) {
        free(ai);
        fprintf(stderr, "\033[31m[ERROR]\033[0m  Team not found\n");
        return;
    }
    TAILQ_INIT(&ai->commands);
    TAILQ_INIT(&ai->incantations);
    if (!connect_ai(server, payload, ai))
        return;
    verbose(server, "New AI connected\n");
    pnw(server, ai);
}

static void save_cmd_ai(
    ai_t *ai,
    const ai_command_t *command,
    const char *message)
{
    ai_cmd_t *cmd = calloc(1, sizeof(ai_cmd_t));

    if (!cmd)
        return;
    *cmd = (ai_cmd_t){ .func = command->func, .time = command->time };
    memcpy(cmd->cmd, message, strlen(message));
    TAILQ_INSERT_TAIL(&ai->commands, cmd, entries);
}

static uint8_t get_nb_commands(
    const ai_t *ai)
{
    uint8_t nb = 0;
    ai_cmd_t *cmd;

    TAILQ_FOREACH(cmd, &ai->commands, entries)
        nb++;
    return nb;
}

static bool handle_cmd_ai(
    zappy_server_t *server,
    ai_t *ai,
    const ai_command_t *command,
    const char *message)
{
    const uint8_t len = strlen(command->cmd);

    if (strncmp(message, command->cmd, len))
        return false;
    if (get_nb_commands(ai) >= 10) {
        ai->state = SKIPPED;
        return false;
    }
    if (command->time == 0) {
        command->func(server, ai, message + len + 1);
        return true;
    }
    if (command->check && !command->check(server, ai, message + len + 1)) {
        protocol_server_send(server->socket, ai->fd, "ko");
        return false;
    }
    save_cmd_ai(ai, command, message + len);
    return true;
}

void handle_event_ai(
    zappy_server_t *server,
    const protocol_payload_t *payload)
{
    ai_t *ai = ai_get_by_fd(server, payload->fd);

    if (ai->state == DEAD || ai->state == SKIPPED)
        return;
    for (uint8_t i = 0; ai_cmds[i].func; ++i)
        if (handle_cmd_ai(server, ai, &ai_cmds[i], payload->message))
            return;
    protocol_server_send(server->socket, payload->fd, "ko");
}

ai_t *ai_get_by_id(
    const zappy_server_t *server,
    const uint16_t id)
{
    ai_t *ai;

    TAILQ_FOREACH(ai, &server->ais, entries)
        if (ai->id == id)
            return ai;
    return NULL;
}

ai_t *ai_get_by_fd(
    const zappy_server_t *server,
    const int fd)
{
    ai_t *ai;

    TAILQ_FOREACH(ai, &server->ais, entries)
        if (ai->fd == fd)
            return ai;
    return NULL;
}

uint16_t ai_get_nb_by_pos(
    const zappy_server_t *server,
    const vector2_t *pos)
{
    uint16_t nb = 0;
    ai_t *ai;

    TAILQ_FOREACH(ai, &server->ais, entries)
        if (ai->pos.x == pos->x && ai->pos.y == pos->y)
            nb++;
    return nb;
}
