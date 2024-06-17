/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** look
*/

#include <stdio.h>
#include <string.h>

#include "server/ai_header.h"

static void add_element_to_message(char *message, const char *element)
{
    snprintf(message + strlen(message), DATA_SIZE - strlen(message),
        "%s", element);
}

static void look_tile(
    const zappy_server_t *server,
    char *formatted_message,
    const vector2_t *pos)
{
    const inventory_t *tile = &server->map[pos->y][pos->x];

    for (int nb_ai = ai_get_nb_by_pos(server, pos); nb_ai > 0; nb_ai--)
        add_element_to_message(formatted_message, " player");
    for (int nb_food = tile->food; nb_food > 0; nb_food--)
        add_element_to_message(formatted_message, " food");
    for (int nb_linemate = tile->linemate; nb_linemate > 0; nb_linemate--)
        add_element_to_message(formatted_message, " linemate");
    for (int nb_deraumere = tile->deraumere; nb_deraumere > 0; nb_deraumere--)
        add_element_to_message(formatted_message, " deraumere");
    for (int nb_sibur = tile->sibur; nb_sibur > 0; nb_sibur--)
        add_element_to_message(formatted_message, " sibur");
    for (int nb_mendiane = tile->mendiane; nb_mendiane > 0; nb_mendiane--)
        add_element_to_message(formatted_message, " mendiane");
    for (int nb_phiras = tile->phiras; nb_phiras > 0; nb_phiras--)
        add_element_to_message(formatted_message, " phiras");
    for (int nb_thystame = tile->thystame; nb_thystame > 0; nb_thystame--)
        add_element_to_message(formatted_message, " thystame");
}

void look(
    const zappy_server_t *server,
    ai_t *ai,
    UNUSED const char *message)
{
    char formatted_message[DATA_SIZE] = {0};

    snprintf(formatted_message, DATA_SIZE, "[");
    for (int y = 0; y <= ai->level; y++) {
        for (int x = -y; x <= y; x++) {
            look_tile(server, formatted_message, &(vector2_t){
                (server->width + ai->pos.x + x) % server->width,
                (server->height + ai->pos.y + y) % server->height});
            add_element_to_message(formatted_message, ",");
        }
    }
    formatted_message[strlen(formatted_message) - 1] = '\0';
    add_element_to_message(formatted_message, " ]");
    protocol_server_send(server->socket, ai->fd, formatted_message);
}
