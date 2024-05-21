/*
** EPITECH PROJECT, 2024
** Protocol
** File description:
** protocol/client
*/

#ifndef PROTOCOL_CLIENT_H
    #define PROTOCOL_CLIENT_H

    #include <sys/queue.h>
    #include <stdbool.h>

    #include "./data.h"

typedef struct protocol_client_s {
    fd_set master_read_fds;
    fd_set master_write_fds;
    fd_set readfds;
    fd_set writefds;
    int sockfd;
    protocol_network_data_t network_data;
    bool is_connected;
    TAILQ_ENTRY(protocol_client_s) entries;
    TAILQ_HEAD(, protocol_payload_s) payloads;
} protocol_client_t;

/**
 * @brief Create a new protocol client
 *
 * @param ip The ip to connect to
 * @param port The port to connect to
 * @return protocol_client_t* The created client
 */
protocol_client_t *protocol_client_create(
    const char *ip,
    int port);

/**
 * @brief Close the client
 *
 * @param client The client to close
 */
void protocol_client_close(
    protocol_client_t *client);

/**
 * @brief Check if the client is connected
 *
 * @param client The client to check
 * @return true If the client is connected
 * @return false If the client is not connected
 */
bool protocol_client_is_connected(
    const protocol_client_t *client);

/**
 * @brief Listen for incoming packets
 *
 * @param client The client to listen with
 * @return protocol_payload_t* The received payload
 */
protocol_payload_t *protocol_client_listen(
    protocol_client_t *client);

/**
 * @brief Send a packet to the server
 *
 * @param client The client to send the packet with
 * @param type The type of the packet
 * @param data The data to send
 * @param size The size of the data
 * @return true If the packet was sent
 * @return false If the packet was not sent
 */
bool protocol_client_send_packet(
    const protocol_client_t *client,
    uint16_t type,
    const void *data,
    int size);

#endif //PROTOCOL_CLIENT_H
