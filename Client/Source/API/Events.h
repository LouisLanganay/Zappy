/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Events
*/

#ifndef EVENTS_H_
#define EVENTS_H_

    #include <stdint.h>

    typedef enum {
        EVT_UNKNOWN = 0,
        EVT_MAP_SIZE,
        EVT_TILE_CONTENT,
        EVT_MAP_CONTENT,
        EVT_TEAMS_NAME,
        EVT_PLAYER_ADD,
        EVT_PLAYER_POSITION,
        EVT_PLAYER_LEVEL,
        EVT_PLAYER_INVENTORY,
        EVT_EXPULSION,
        EVT_BROADCAST,
        EVT_INCANTATION_START,
        EVT_INCANTATION_END,
        EVT_PLAYER_EGG_LAYING,
        EVT_RESOURCE_DROP,
        EVT_RESOURCE_COLLECT,
        EVT_PLAYER_DEATH,
        EVT_EGG_LAID,
        EVT_EGG_CONNECT,
        EVT_EGG_DEATH,
        EVT_TIME_UNIT_REQUEST,
        EVT_TIME_UNIT_CHANGE,
        EVT_GAME_END,
        EVT_SERVER_MESSAGE,
        EVT_UNKNOWN_COMMAND,
        EVT_BAD_PARAMETER,
        EVT_START
    } event_type_t;

    typedef struct {
        int width;
        int height;
    } map_size_t;

    typedef struct {
        int x;
        int y;
        int resources[7];
    } tile_content_t;

    typedef struct {
        int width;
        int height;
        tile_content_t* tiles;
    } map_content_t;

    typedef struct {
        char** teams;
    } teams_name_t;

    typedef struct {
        int playerNumber;
        int x;
        int y;
        int orientation;
        int level;
        char teamName[50];
    } player_add_t;

    typedef struct {
        int playerNumber;
        int x;
        int y;
    } player_position_t;

    typedef struct {
        int playerNumber;
        int level;
    } player_level_t;

    typedef struct {
        int playerNumber;
        int resources[7];
    } player_inventory_t;

    typedef struct {
        int playerNumber;
    } expulsion_t;

    typedef struct {
        int playerNumber;
        char message[512];
    } broadcast_t;

    typedef struct {
        int x;
        int y;
        int incantationLevel;
        int* players;
    } incantation_start_t;

    typedef struct {
        int x;
        int y;
        int incantationResult;
    } incantation_end_t;

    typedef struct {
        int playerNumber;
    } player_egg_laying_t;

    typedef struct {
        int playerNumber;
        int resourceType;
    } resource_drop_t;

    typedef struct {
        int playerNumber;
        int resourceType;
    } resource_collect_t;

    typedef struct {
        int playerNumber;
    } player_death_t;

    typedef struct {
        int eggNumber;
        int playerNumber;
        int x;
        int y;
    } egg_laid_t;

    typedef struct {
        int eggNumber;
    } egg_connect_t;

    typedef struct {
        int eggNumber;
    } egg_death_t;

    typedef struct {
        int timeUnit;
    } time_unit_request_t;

    typedef struct {
        int timeUnit;
    } time_unit_change_t;

    typedef struct {
        char* winnerTeam;
    } game_end_t;

    typedef struct {
        char* message;
    } server_message_t;

    typedef struct {
    } unknown_command_t;

    typedef struct {
    } bad_parameter_t;

    typedef struct {
    } start_t;

#endif /* !EVENTS_H_ */
