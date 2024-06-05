/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** sst
*/

#include <stdio.h>

#include "server/gui.h"
#include "server.h"

void sst(
    zappy_server_t *server,
    const int interlocutor,
    const char *message)
{
    char formatted_message[DATA_SIZE];
    uint16_t freq;

    if (sscanf(message, " %hd", &freq) != 1) {
        sbp(server, interlocutor);
        return;
    }
    server->freq = freq;
    snprintf(formatted_message, DATA_SIZE, "sst %d\n", freq);
    gui_send_to_all(server, formatted_message);
}
