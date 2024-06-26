/*
** EPITECH PROJECT, 2024
** Protocol
** File description:
** protocol/client
*/

#ifndef PROTOCOL_CLIENT_H
    #define PROTOCOL_CLIENT_H

    #include <stdbool.h>

    #include "data.h"

typedef struct protocol_client_s {
    fd_set master_read_fds;
    fd_set master_write_fds;
    fd_set readfds;
    fd_set writefds;
    int sockfd;
    protocol_network_data_t network_data;
    bool is_connected;
    char buffer[DATA_SIZE];
    TAILQ_ENTRY(protocol_client_s) entries;
    TAILQ_HEAD(, protocol_payload_s) payloads;
} protocol_client_t;

/**
 * @brief Create a new protocol client
 *
 * @param ip The ip to connect to
 * @param port The port to connect to
 * @return protocol_client_t* The created client
 *
 * @note The client must be closed after use with protocol_client_close
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
 *
 * @note The payload must be freed after use
 */
protocol_payload_t *protocol_client_listen(
    protocol_client_t *client);

/**
 * @brief Send a message to the server
 *
* @param client The client to send the message with
 * @param format The format of the message to send
 * @param ... The arguments to format the message with
 * @return true If the message was sent
 * @return false If the message was not sent
 */
bool protocol_client_send(
    const protocol_client_t *client,
    const char *format,
    ...);

#endif //PROTOCOL_CLIENT_H
