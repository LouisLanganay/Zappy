/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** gui
*/

#ifndef GUI_H
    #define GUI_H

    #include "server.h"

/**
 * @brief Send the map size when EVT_MSZ is received from a GUI
 *
 * @param server The server_t struct
 * @param payload The payload of the packet
 *
 * @note Call EVT_MSZ
 * @note Send EVT_MSZ with a vector2_t
 */
void msz(const zappy_server_t *server, const protocol_payload_t *payload);
/**
 * @brief Send the tile content when EVT_BCT is received from a GUI
 *
 * @param server The server_t struct
 * @param payload The payload of the packet
 *
 * @note Call EVT_BCT with a vector2_t
 * @note Send EVT_BCT with a tile_t
 */
void bct(const zappy_server_t *server, const protocol_payload_t *payload);
/**
 * @brief Send the content of all tiles when EVT_MCT is received from a GUI
 *
 * @param server The server_t struct
 * @param payload The payload of the packet
 *
 * @note Call EVT_MCT
 * @note Send EVT_BCT with a tile_t for each tile
 */
void mct(const zappy_server_t *server, const protocol_payload_t *payload);
/**
 * @brief Send the name of all teams when EVT_TNA is received from a GUI
 *
 * @param server The server_t struct
 * @param payload The payload of the packet
 *
 * @note Call EVT_PPO
 * @note Send EVT_PPO with a char* for each team
 */
void tna(const zappy_server_t *server, const protocol_payload_t *payload);
/**
 * @brief Send the content of a ai when a new ai connect
 *
 * @param server The server_t struct
 * @param ai The ai_t struct
 *
 * @note Send EVT_PNW with a ai_info_t
 */
void pnw(const zappy_server_t *server, const ai_t *ai);
/**
 * @brief Send the position of a ai when EVT_PPO is received from a GUI
 *
 * @param server The server_t struct
 * @param payload The payload of the packet
 *
 * @note Call EVT_PPO with a uint16_t
 * @note Send EVT_PPO with a ai_pos_t
 */
void ppo(const zappy_server_t *server, const protocol_payload_t *payload);
/**
 * @brief Send the level of a ai when EVT_PLV is received from a GUI
 *
 * @param server The server_t struct
 * @param payload The payload of the packet
 *
 * @note Call EVT_PLV with a uint16_t
 * @note Send EVT_PLV with a ai_level_t
 */
void plv(const zappy_server_t *server, const protocol_payload_t *payload);
/**
 * @brief Send the inventory of a ai when EVT_PIN is received from a GUI
 *
 * @param server The server_t struct
 * @param payload The payload of the packet
 *
 * @note Call EVT_PIN with a uint16_t
 * @note Send EVT_PIN with a ai_inventory_t
 */
void pin(const zappy_server_t *server, const protocol_payload_t *payload);
/**
 * @brief Send a message to all GUI when a ai is expelled
 *
 * @param server The server_t struct
 * @param ai The ai_t struct
 *
 * @note Send EVT_PEX with a uint16_t
 */
void pex(const zappy_server_t *server, const ai_t *ai);
/**
 * @brief Send a message to all GUI
 *
 * @param server The server_t struct
 * @param msg The message to send
 *
 * @note Send EVT_SGT with a char*
 */
void smg(const zappy_server_t *server, const char *msg);
/**
 * @brief Send when a unknown command is received
 *
 * @param server The server_t struct
 * @param payload The payload of the packet
 *
 * @note Send EVT_SBP
 */
void suc(const zappy_server_t *server, const protocol_payload_t *payload);
/**
 * @brief Send when a invalid command parameter is received
 *
 * @param server The server_t struct
 * @param payload The payload of the packet
 *
 * @note Send EVT_SBP
 */
void sbp(const zappy_server_t *server, const protocol_payload_t *payload);

static const struct {
    gui_event_t event;
    void (*func)(const zappy_server_t *server, const protocol_payload_t *payload);
} gui_cmds[] = {
    {EVT_MSZ, msz},
    {EVT_BCT, bct},
    {EVT_MCT, mct},
    {EVT_TNA, tna},
    {EVT_PPO, ppo},
    {EVT_PLV, plv},
    {EVT_PIN, pin},
    {EVT_UNKNOWN, NULL}
};

#endif //GUI_H
