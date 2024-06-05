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

    #define UNUSED __attribute__((unused))

typedef enum {
    CONNECTION_SELF,
    CONNECTION_AI,
    CONNECTION_GUI,
    CONNECTION_UNKNOWN,
} connection_t;

typedef enum {
    NORTH = 1,
    EAST = 2,
    SOUTH = 3,
    WEST = 4,
} orientation_t;

typedef struct {
    uint16_t x;
    uint16_t y;
} vector2_t;

typedef struct {
    uint16_t food;
    uint16_t linemate;
    uint16_t deraumere;
    uint16_t sibur;
    uint16_t mendiane;
    uint16_t phiras;
    uint16_t thystame;
} inventory_t;

typedef struct team_s {
    uint16_t id;
    char name[64];

    TAILQ_ENTRY(team_s) entries;
} team_t;

typedef struct ai_cmd_s {
    char *cmd;
    TAILQ_ENTRY(ai_cmd_s) entries;
} ai_cmd_t;

typedef struct ai_s {
    int fd;

    uint16_t id;
    team_t *team;

    vector2_t pos;
    orientation_t orientation;
    uint16_t level;
    inventory_t inventory;

    TAILQ_ENTRY(ai_s) entries;
    TAILQ_HEAD(, ai_cmd_t) commands;
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
    TAILQ_HEAD(teamhead, team_s) teams;
    inventory_t **map;
    TAILQ_HEAD(, gui_s) guis;
} zappy_server_t;

bool zappy_server(
    zappy_server_t *server);
void server_init(
    zappy_server_t *server);
ai_t *get_ai_by_id(
    const zappy_server_t *server,
    uint16_t id);
void gui_send_to_all(
    const zappy_server_t *server,
    const char *message);

#endif //SERVER_H
