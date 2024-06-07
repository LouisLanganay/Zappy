/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** pdr
*/

#include "server/gui.h"

#include <string.h>

static void pdr3(
    zappy_server_t *server,
    const int interlocutor,
    const ai_t *ai,
    const char *message
)
{
    if (strcmp(message, "phiras") == 0) {
        protocol_server_send(server->socket, interlocutor, "%d\n",
        ai->inventory.phiras);
        return;
    }
    if (strcmp(message, "thystame") == 0) {
        protocol_server_send(server->socket, interlocutor, "%d\n",
        ai->inventory.thystame);
        return;
    }
    sbp(server, interlocutor);
}

static void pdr2(
    zappy_server_t *server,
    const int interlocutor,
    const ai_t *ai,
    const char *message)
{
    if (strcmp(message, "deraumere") == 0) {
        protocol_server_send(server->socket, interlocutor, "%d\n",
        ai->inventory.deraumere);
        return;
    }
    if (strcmp(message, "sibur") == 0) {
        protocol_server_send(server->socket, interlocutor, "%d\n",
        ai->inventory.sibur);
        return;
    }
    if (strcmp(message, "mendiane") == 0) {
        protocol_server_send(server->socket, interlocutor, "%d\n",
        ai->inventory.mendiane);
        return;
    }
    pdr3(server, interlocutor, ai, message);
}

void pdr(
    zappy_server_t *server,
    const int interlocutor,
    const char *message)
{
    const ai_t *ai = get_ai_by_id(server, interlocutor);

    if (!ai) {
        sbp(server, interlocutor);
        return;
    }
    protocol_server_send(server->socket, interlocutor, "pdr %d", ai->id);
    if (strcmp(message, "food") == 0) {
        protocol_server_send(server->socket, interlocutor, "%d\n",
        ai->inventory.food);
    }
    if (strcmp(message, "linemate") == 0) {
        protocol_server_send(server->socket, interlocutor, "%d\n",
        ai->inventory.linemate);
        return;
    }
    pdr2(server, interlocutor, ai, message);
}
