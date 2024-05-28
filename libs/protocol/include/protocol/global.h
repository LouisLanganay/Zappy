/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** protocol/global
*/

#ifndef GLOBAL_H
    #define GLOBAL_H

    #include "./data.h"

/**
 * @brief Receive a message from a payload
 * @brief (Convert the payload packet to a string)
 *
 * @param payload The payload to receive the message from
 * @return char* The received message
 *
 * @note The message must be freed after use
 */
char *protocol_receive_message(
    const protocol_payload_t *payload);

#endif //GLOBAL_H
