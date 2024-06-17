/*
** EPITECH PROJECT, 2024
** Protocol
** File description:
** protocol/data
*/

#ifndef PROTOCOL_DATA_H
    #define PROTOCOL_DATA_H

    #include <netinet/in.h>
    #include <sys/queue.h>

    #define DATA_SIZE 1024

typedef struct {
    int sockfd;
    struct sockaddr_in server_addr;
} protocol_network_data_t;

typedef struct {
    uint16_t type;
    uint8_t data[DATA_SIZE];
} protocol_packet_t;

typedef struct protocol_payload_s {
    protocol_packet_t packet;
    int fd;
    TAILQ_ENTRY(protocol_payload_s) entries;
} protocol_payload_t;

#endif //PROTOCOL_DATA_H
