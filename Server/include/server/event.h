/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** event
*/

#ifndef EVENT_H
    #define EVENT_H

typedef enum {
    EVT_MSZ,
    EVT_BCT,
    EVT_MCT,
    EVT_TNA,
    EVT_PNW,
    EVT_PPO,
    EVT_PLV,
    EVT_PIN,
    EVT_PEX,
    EVT_PBC,
    EVT_PIC,
    EVT_PIE,
    EVT_PFK,
    EVT_PDR,
    EVT_PGT,
    EVT_PDI,
    EVT_ENW,
    EVT_EBO,
    EVT_EDI,
    EVT_SGT,
    EVT_SST,
    EVT_SEG,
    EVT_SMG,
    EVT_SUC,
    EVT_SBP,

    EVT_UNKNOWN = -1,
} gui_event_t;

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

typedef struct {
    vector2_t pos;
    inventory_t inventory;
} tile_t;

typedef struct {
    uint16_t id;
    vector2_t pos;
    orientation_t orientation;
    uint16_t level;
    char *team;
} ai_info_t;

typedef struct {
    uint16_t id;
    vector2_t pos;
    orientation_t orientation;
} ai_pos_t;

typedef struct {
    uint16_t id;
    uint16_t level;
} ai_level_t;

typedef struct {
    uint16_t id;
    vector2_t pos;
    inventory_t inventory;
} ai_inventory_t;

typedef struct {
    uint16_t id;
    char *msg;
} broadcast_t;

#endif //EVENT_H
