/**
 * @file tcp_client.h
 * @author MK
 * @brief 
 * @version 0.1
 * @date 2024-11-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef __TCP_CLIENT_H
#define __TCP_CLIENT_H

//              INCLUDES
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

//              MACROS
#define SERVER_IP "192.168.119.120"
#define SERVER_PORT 8080
#define BUFFER_SIZE 1024

//              TYPE DEFINITIONS
typedef struct client_data
{
    WSADATA wsaData;
    SOCKET clientSocket;
    struct sockaddr_in serverAddr;
}client_data_t;

//              FUNCTION PROTOS
void clientInit(client_data_t *data);
void clientCleanup(client_data_t *data);
void clientSend(client_data_t *data, const char* msg, int msg_len);
void clientRecv(client_data_t *data, char *buffer);


#endif /* __TCP_CLIENT_H */