/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** server
*/

#ifndef SERVER_H
    #define SERVER_H

    #include <stdbool.h>
    #include <time.h>

    #include "protocol/server.h"

    #define UNUSED __attribute__((unused))
    #define TEAM_NAME_SIZE 64
    #define FOOD_SATURATION 126
    #define EGG_LAY_TIME 600


typedef enum {
    ALIVE,
    DEAD,
    INCANTATE,
    SKIPPED,
} ai_state_t;

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


static const char RESSOURCES_NAMES[][10] = {
    "food",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame"
};

typedef struct team_s {
    uint16_t id;
    char name[TEAM_NAME_SIZE];
    uint16_t slots;

    TAILQ_ENTRY(team_s) entries;
} team_t;

typedef struct zappy_server_s zappy_server_t;
typedef struct ai_s ai_t;
typedef struct ai_cmd_s {
    char cmd[DATA_SIZE];
    void (*func)(
        zappy_server_t *server,
        ai_t *ai,
        const char *message);
    uint16_t time;

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

    uint16_t life_span;
    ai_state_t state;

    TAILQ_HEAD(, ai_cmd_s) commands;
    TAILQ_HEAD(, incantation_s) incantations;

    TAILQ_ENTRY(ai_s) entries;
} ai_t;

typedef struct incantation_s {
    ai_t *ai;

    TAILQ_ENTRY(incantation_s) entries;
} incantation_t;

typedef struct gui_s {
    int fd;

    TAILQ_ENTRY(gui_s) entries;
} gui_t;

typedef struct egg_s {
    uint16_t id;
    team_t *team;
    uint16_t lay_time;
    vector2_t pos;

    TAILQ_ENTRY(egg_s) entries;
} egg_t;

typedef struct zappy_server_s {
    protocol_server_t *socket;

    uint16_t port;
    uint16_t width;
    uint16_t height;
    uint16_t clients_nb;
    uint16_t freq;
    bool verbose;

    bool is_game_end;
    team_t *winner;

    inventory_t base_ressources;
    inventory_t ressources;

    struct timespec last_update;
    uint8_t meteor_time;

    uint16_t ai_id;
    uint16_t egg_id;

    TAILQ_HEAD(, ai_s) ais;
    TAILQ_HEAD(teamhead, team_s) teams;
    TAILQ_HEAD(, egg_s) eggs;
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
void create_ai(
    zappy_server_t *server,
    const protocol_payload_t *payload);
void handle_event_ai(
    zappy_server_t *server,
    const protocol_payload_t *payload);
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
void create_gui(
    zappy_server_t *server,
    const protocol_payload_t *payload);
void handle_event_gui(
    zappy_server_t *server,
    const protocol_payload_t *payload);
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
// egg
uint16_t egg_spawn(
    zappy_server_t *server,
    const ai_t *ai);
egg_t *egg_pop_by_team(
    zappy_server_t *server,
    const team_t *team);

#endif //SERVER_H
