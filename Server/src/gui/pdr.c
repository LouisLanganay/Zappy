/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** pdr
*/

#include "server/gui.h"

#include <string.h>

static void pdr2(
    zappy_server_t *server,
    const int interlocutor,
    const ai_t *ai,
    const char *message)
{
    if (strcmp(message, "mendiane") == 0)
        protocol_server_send_message(server->socket, interlocutor, "%d\n",
        ai->inventory.mendiane);
    else if (strcmp(message, "phiras") == 0)
        protocol_server_send_message(server->socket, interlocutor, "%d\n",
        ai->inventory.phiras);
    else if (strcmp(message, "thystame") == 0)
        protocol_server_send_message(server->socket, interlocutor, "%d\n",
        ai->inventory.thystame);
    else
        sbp(server, interlocutor);
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
    protocol_server_send_message(server->socket, interlocutor, "pdr %d", ai->id);
    if (strcmp(message, "food") == 0)
        protocol_server_send_message(server->socket, interlocutor, "%d\n",
        ai->inventory.food);
    else if (strcmp(message, "linemate") == 0)
        protocol_server_send_message(server->socket, interlocutor, "%d\n",
        ai->inventory.linemate);
    else if (strcmp(message, "deraumere") == 0)
        protocol_server_send_message(server->socket, interlocutor, "%d\n",
        ai->inventory.deraumere);
    else if (strcmp(message, "sibur") == 0)
        protocol_server_send_message(server->socket, interlocutor, "%d\n",
        ai->inventory.sibur);
   pdr2(server, interlocutor, ai, message);
}
