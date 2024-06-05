/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** gui
*/

#ifndef GUI_H
    #define GUI_H

    #include <stddef.h>

    #include "server.h"

/**
 * @brief Send the map size when msz is received from a GUI
 *
 * @param server The server_t struct
 * @param interlocutor The fd of the GUI
 * @param message The message of the command
 *
 * @note Call msz
 * @note Send msz with the width and height of the map
 */
void msz(
    zappy_server_t *server,
    int interlocutor,
    const char *message);
/**
 * @brief Send the tile content when bct is received from a GUI
 *
 * @param server The server_t struct
 * @param interlocutor The fd of the GUI
 * @param message The message of the command
 *
 * @note Call bct with the x and y of the tile
 * @note Send bct with the position and content of the tile
 */
void bct(
    zappy_server_t *server,
    int interlocutor,
    const char *message);
/**
 * @brief Send the content of all tiles when mct is received from a GUI
 *
 * @param server The server_t struct
 * @param interlocutor The fd of the GUI
 * @param message The message of the command
 *
 * @note Call mct
 * @note Send for each tile bct with the position and content of the tile
 */
void mct(
    zappy_server_t *server,
    int interlocutor,
    const char *message);
/**
 * @brief Send the name of all teams when tna is received from a GUI
 *
 * @param server The server_t struct
 * @param interlocutor The fd of the GUI
 * @param message The message of the command
 *
 * @note Call tna
 * @note Send for each team tna with the name of the team
 */
void tna(
    zappy_server_t *server,
    int interlocutor,
    const char *message);
/**
 * @brief Send the content of a ai when a new ai connect
 *
 * @param server The server_t struct
 * @param ai The ai_t struct
 *
 * @note Send pnw with the id, position, orientation, level and team of the ai
 */
void pnw(
    zappy_server_t *server,
    const ai_t *ai);
/**
 * @brief Send the position of a ai when ppo is received from a GUI
 *
 * @param server The server_t struct
 * @param interlocutor The fd of the GUI
 * @param message The message of the command
 *
 * @note Call ppo with the id of the ai
 * @note Send ppo with the id of the ai and the position and orientation
 */
void ppo(
    zappy_server_t *server,
    int interlocutor,
    const char *message);
/**
 * @brief Send the level of a ai when plv is received from a GUI
 *
 * @param server The server_t struct
 * @param interlocutor The fd of the GUI
 * @param message The message of the command
 *
 * @note Call plv with the id of the ai
 * @note Send plv with the id of the ai and the level
 */
void plv(
    zappy_server_t *server,
    int interlocutor,
    const char *message);
/**
 * @brief Send the inventory of a ai when pin is received from a GUI
 *
 * @param server The server_t struct
 * @param interlocutor The fd of the GUI
 * @param message The message of the command
 *
 * @note Call pin with the id of the ai
 * @note Send pin with the id of the ai and the inventory
 */
void pin(
    zappy_server_t *server,
    int interlocutor,
    const char *message);
/**
 * @brief Send a message to all GUI when a ai is expelled
 *
 * @param server The server_t struct
 * @param interlocutor The id of the ai
 *
 * @note Send pex with the id of the ai
 */
void pex(
    zappy_server_t *server,
    int interlocutor);
/**
 * @brief Send the frequency of the server when sgt is received from a GUI
 *
 * @param server The server_t struct
 * @param interlocutor The fd of the GUI
 * @param message The message of the command
 *
 * @note Call sgt
 * @note Send sgt with the frequency of the server
 */
void sgt(
    zappy_server_t *server,
    int interlocutor,
    const char *message);
/**
 * @brief Send and set the frequency of the server when sst is
 * received from a GUI
 *
 * @param server The server_t struct
 * @param interlocutor The fd of the GUI
 * @param message The message of the command
 *
 * @note Call sst with the frequency to set
 * @note Send sst with the frequency of the server
 */
void sst(
    zappy_server_t *server,
    int interlocutor,
    const char *message);
/**
 * @brief Send a message to all GUI
 *
 * @param server The server_t struct
 * @param message The message to send
 *
 * @note Send for each GUI smg with the message
 */
void smg(
    zappy_server_t *server,
    const char *message);
/**
 * @brief Send when a unknown command is received
 *
 * @param server The server_t struct
 * @param interlocutor The fd of the GUI
 *
 * @note Send suc
 */
void suc(
    zappy_server_t *server,
    int interlocutor);
/**
 * @brief Send when a invalid command parameter is received
 *
 * @param server The server_t struct
 * @param interlocutor The fd of the GUI
 *
 * @note Send sbp
 */
void sbp(
    zappy_server_t *server,
    int interlocutor);

/**
 * @brief Start an incantation
 *
 * @param server The server_t struct
 * @param interlocutor The fd of the GUI
 *
 * @note Send pic with the position of the tile and the player number
 */
void pic(
    zappy_server_t *server,
    int interlocutor);

static const struct {
    const char *cmd;
    void (*func)(
        zappy_server_t *server,
        int interlocutor,
        const char *message);
} gui_cmds[] = {
    {"msz", msz},
    {"bct", bct},
    {"mct", mct},
    {"tna", tna},
    {"ppo", ppo},
    {"plv", plv},
    {"pin", pin},
    {NULL, NULL}
};

#endif //GUI_H
