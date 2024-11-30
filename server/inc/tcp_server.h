/**
 * @file tcp_server.h
 * @author MK
 * @brief 
 * @version 0.1
 * @date 2024-11-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef __TCP_SERVER_H
#define __TCP_SERVER_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define PORT        8080
#define BUFFER_SIZE  1024

typedef struct server_data
{
    WSADATA wsaData;
    SOCKET serverSocket;
    SOCKET clientSocket;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
}server_data_t;

void printClientIP(server_data_t *data);
void serverInit(server_data_t *data);
void serverCleanup(server_data_t *data);
void serverAcceptConn(server_data_t *data, int *clientAddrSize);
int serverRxAndEcho(server_data_t *data, char *buffer, int buf_len);

#endif /* __TCP_SERVER_H */