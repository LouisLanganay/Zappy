/*
** EPITECH PROJECT, 2024
** Protocol
** File description:
** protocol/server
*/

#ifndef PROTOCOL_SERVER_H
    #define PROTOCOL_SERVER_H

    #include "./client.h"


typedef struct protocol_connection_s {
    int fd;
    TAILQ_ENTRY(protocol_connection_s) entries;
} protocol_connection_t;

typedef struct {
    protocol_network_data_t network_data;
    fd_set master_read_fds;
    fd_set master_write_fds;
    fd_set read_fds;
    fd_set write_fds;
    TAILQ_HEAD(, protocol_client_s) clients;
    TAILQ_HEAD(, protocol_payload_s) payloads;
    TAILQ_HEAD(, protocol_connection_s) new_connections;
    TAILQ_HEAD(, protocol_connection_s) lost_connections;
} protocol_server_t;

/**
 * @brief Create a new protocol server
 *
 * @param port The port to listen on
 * @return protocol_server_t* The created server
 *
 * @note The server must be closed after use with protocol_server_close
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
 * @brief Disconnect a client
 *
 * @param server The server to close the client with
 * @param fd The client to close
 */
void protocol_server_close_client(
    protocol_server_t *server,
    int fd);

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
 *
 * @note The payload must be freed after use
 */
protocol_payload_t *protocol_server_listen(
    protocol_server_t *server);

/**
 * @brief Send a message to a client
 *
 * @param server The server to send the message with
 * @param client_fd The client to send the message to
 * @param format The format of the message to send
 * @param ... The arguments to format the message with
 * @return true If the message was sent
 * @return false If the message was not sent
 */
bool protocol_server_send(
    protocol_server_t *server,
    int client_fd,
    const char *format,
    ...);

#endif //PROTOCOL_SERVER_H
