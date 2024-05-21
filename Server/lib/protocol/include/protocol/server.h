/*
** EPITECH PROJECT, 2024
** Protocol
** File description:
** protocol/server
*/

#ifndef PROTOCOL_SERVER_H
    #define PROTOCOL_SERVER_H

    #include "./client.h"

typedef struct {
    protocol_network_data_t network_data;
    fd_set master_read_fds;
    fd_set master_write_fds;
    fd_set read_fds;
    fd_set write_fds;
    TAILQ_HEAD(, protocol_client_s) clients;
    TAILQ_HEAD(, protocol_payload_s) payloads;
} protocol_server_t;

/**
 * @brief Create a new protocol server
 *
 * @param port The port to listen on
 * @return protocol_server_t* The created server
 */
protocol_server_t *protocol_server_create(
    int port);

/**
 * @brief Close the server
 *
 * @param server The server to close
 */
void protocol_server_close(
    protocol_server_t *server);

/**
 * @brief Check if the server is open
 *
 * @return true If the server is open
 * @return false If the server is closed
 */
bool protocol_server_is_open(void);

/**
 * @brief Listen for incoming packets
 *
 * @param server The server to listen with
 * @return protocol_payload_t* The received payload
 */
protocol_payload_t *protocol_server_listen(
    protocol_server_t *server);

/**
 * @brief Send a packet to a client
 *
 * @param packet The packet to send
 * @param client_fd The client to send the packet to
 * @param server The server to send the packet with
 * @return true If the packet was sent
 * @return false If the packet was not sent
 */
bool protocol_server_send_packet(
    const protocol_packet_t *packet,
    int client_fd,
    protocol_server_t *server);

/**
 * @brief Send a packet type to a client
 *
 * @param type The type of the packet to send
 * @param client_fd The client to send the packet to
 * @param server The server to send the packet with
 * @return true If the packet was sent
 * @return false If the packet was not sent
 */
bool protocol_server_send_packet_type(
    uint16_t type,
    int client_fd,
    protocol_server_t *server);

#endif //PROTOCOL_SERVER_H
