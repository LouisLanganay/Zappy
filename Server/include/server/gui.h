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

/**
 * @brief End an incantation
 *
 * @param server The server_t struct
 * @param interlocutor The fd of the GUI
 *
 * @note Send pie with the position of the tile and the result of the incantation
 */
void pie(
    const zappy_server_t *server,
    int interlocutor);

/**
 * @brief egg laying by the player
 *
 * @param server The server_t struct
 * @param interlocutor The fd of the GUI
 *
 * @note Send pfk with the player number
*/
void pfk(
    const zappy_server_t *server,
    int interlocutor);
/**
 * @brief ressource dropping
 *
 * @param server The server_t struct
 * @param interlocutor The fd of the GUI
 * @param message The message of the command
 *
 * @note Send pdr with the player number and the actual ressource in the inventory
*/
void pdr(
    zappy_server_t *server,
    const int interlocutor,
    const char *message);

/**
 * @brief ressource taking
 *
 * @param server The server_t struct
 * @param interlocutor The fd of the GUI
 * @param message The message of the command
 *
 * @note Send pgt with the player number and the actual ressource in the inventory
*/
void pgt(
    zappy_server_t *server,
    const int interlocutor,
    const char *message);

/**
 * @brief Send the death of a player
 *
 * @param server The server_t struct
 * @param interlocutor The fd of the GUI
 *
 * @note Send pdi with the player number
*/
void pdi(
    const zappy_server_t *server,
    const int interlocutor);

/**
 * @brief An egg is laid by a player
 *
 * @param server The server_t struct
 * @param interlocutor The fd of the GUI
 * @param egg_id The id of the egg
 *
 * @note Send enw with the egg number, the player number and the position of the egg
*/
void enw(
    const zappy_server_t *server,
    const int interlocutor,
    const int egg_id);

/**
 * @brief Player connection for an egg
 *
 * @param server The server_t struct
 * @param interlocutor The fd of the GUI
 * @param egg_id The id of the egg
 *
 * @note Send ebo with the egg number
*/
void ebo(
    const zappy_server_t *server,
    const int interlocutor,
    const int egg_id);

/**
 * @brief Death of an egg
 *
 * @param server The server_t struct
 * @param interlocutor The fd of the GUI
 * @param egg_id The id of the egg
 *
 * @note Send edi with the egg number
*/
void edi(
    const zappy_server_t *server,
    const int interlocutor,
    const int egg_id);

/**
 * @brief Time unit request
 *
 * @param server The server_t struct
 * @param interlocutor The fd of the GUI
 * @param message The message of the command
 *
 * @note Send sgt with the time unit
*/
void sgt(
    const zappy_server_t *server,
    const int interlocutor,
    const char *message);

/**
 * @brief Time unit modification
 *
 * @param server The server_t struct
 * @param interlocutor The fd of the GUI
 * @param message The message of the command
 *
 * @note Send sst with the time unit
*/
void sst(
    const zappy_server_t *server,
    const int interlocutor,
    const char *message);

/**
 * @brief End of the game
 *
 * @param server The server_t struct
 * @param interlocutor The fd of the GUI
 * @param team_name The name of the winner team
 *
 * @note Send seg with the winner team
*/
void seg(
    const zappy_server_t *server,
    const int interlocutor,
    const char *team_name);

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
