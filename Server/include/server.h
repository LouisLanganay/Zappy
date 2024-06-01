/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** server
*/

#ifndef SERVER_H
    #define SERVER_H

    #include <stdbool.h>

    #include "protocol/server.h"
    #include "server/event.h"

typedef struct team_s {
    uint16_t id;
    char name[64];

    TAILQ_ENTRY(team_s) entries;
} team_t;

typedef struct ai_s {
    int fd;

    uint16_t id;
    team_t *team;

    vector2_t pos;
    orientation_t orientation;
    uint16_t level;
    inventory_t inventory;

    TAILQ_ENTRY(ai_s) entries;
} ai_t;

typedef struct gui_s {
    int fd;

    TAILQ_ENTRY(gui_s) entries;
} gui_t;

typedef struct {
    uint16_t port;
    uint16_t width;
    uint16_t height;
    uint16_t clients_nb;
    uint16_t freq;
    bool verbose;

    protocol_server_t *socket;

    TAILQ_HEAD(, ai_s) ais;
    TAILQ_HEAD(, team_s) teams;
    inventory_t **map;
    TAILQ_HEAD(, gui_s) guis;
} zappy_server_t;

ai_t *get_ai_by_id(const zappy_server_t *server, uint16_t id);
void gui_send_to_all(const zappy_server_t *server, const protocol_packet_t *packet);

#endif //SERVER_H
