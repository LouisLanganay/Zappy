/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** protocol/receive_message
*/

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "protocol/data.h"

char *protocol_receive_message(
    const protocol_payload_t *payload)
{
    char *message = calloc(1, DATA_SIZE + 1);

    if (!message) {
        fprintf(stderr, "\033[31m[Error]\033[0m %s\n", strerror(errno));
        return NULL;
    }
    memcpy(message, &payload->packet, DATA_SIZE);
    return message;
}
