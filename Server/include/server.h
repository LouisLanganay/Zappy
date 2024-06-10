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
    #define TEAM_NAME_SIZE 64

typedef enum {
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

typedef union {
    uint16_t resources[7];
    struct {
        uint16_t food;
        uint16_t linemate;
        uint16_t deraumere;
        uint16_t sibur;
        uint16_t mendiane;
        uint16_t phiras;
        uint16_t thystame;
    };
} inventory_t;

typedef struct team_s {
    uint16_t id;
    char name[TEAM_NAME_SIZE];

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
void server_create(
    zappy_server_t *server);
bool handle_payload(
    zappy_server_t *server);
void verbose(
    const zappy_server_t *server,
    const char *format,
    ...);

// ai
void ai_send_to_all(
    const zappy_server_t *server,
    const char *message);
ai_t *ai_get_by_fd(
    const zappy_server_t *server,
    int fd);
ai_t *ai_get_by_id(
    const zappy_server_t *server,
    uint16_t id);
uint16_t ai_get_nb_by_pos(
    const zappy_server_t *server,
    const vector2_t *pos);
// gui
void gui_send_to_all(
    const zappy_server_t *server,
    const char *message,
    ...);

// team
team_t *team_get_by_name(
    const zappy_server_t *server,
    const char *name);
team_t *team_get_by_id(
    const zappy_server_t *server,
    uint16_t id);
uint16_t team_get_empty_slots(
    const zappy_server_t *server,
    const team_t *team);

#endif //SERVER_H
