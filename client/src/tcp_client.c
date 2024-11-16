/**
 * @file tcp_client.c
 * @author MK
 * @brief 
 * @version 0.1
 * @date 2024-11-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "tcp_client.h"

void clientInit(client_data_t *data)
{
    // Step 1: Initialize Winsock
    printf("Initialize Winsock...\n");
    if(WSAStartup(MAKEWORD(2,2), &(data->wsaData)) != 0)
    {
        printf("WSAStartup Failed!\n");
        exit(1);
    }

    // Step 2: Create a client socket
    printf("Create client socket...\n");
    data->clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(data->clientSocket == INVALID_SOCKET)
    {
        printf("Socket creation failed with error: %d\n", WSAGetLastError());
        WSACleanup();
        exit(1);
    }

    // Step 3: Specify the server address and port
    data->serverAddr.sin_family = AF_INET;
    data->serverAddr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &(data->serverAddr.sin_addr));

    // Step 4: Connect to the server
    if(connect(data->clientSocket, (struct sockaddr*)&(data->serverAddr), sizeof(data->serverAddr)) == SOCKET_ERROR)
    {
        printf("Connection to server failed with error: %d\n", WSAGetLastError());
        closesocket(data->clientSocket);
        WSACleanup();
        exit(1);
    }
    printf("Connected to server at %s:%d\n", SERVER_IP, SERVER_PORT);

}

void clientCleanup(client_data_t *data)
{
    // Step 7: Clean up resources
    printf("Clean up resources... :)\n");
    closesocket(data->clientSocket);
    WSACleanup();
}
