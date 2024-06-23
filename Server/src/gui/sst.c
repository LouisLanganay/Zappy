/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** sst
*/

#include <stdio.h>

#include "server/gui.h"

// Response to "sst #n\n"
void sst(
    zappy_server_t *server,
    const int interlocutor,
    const char *message)
{
    uint16_t freq;

    if (sscanf(message, " %hd", &freq) != 1
        || freq < 1 || freq > 10000) {
        sbp(server, interlocutor);
        return;
    }
    server->freq = freq;
    gui_send_to_all(server, "sst %d", server->freq);
}
