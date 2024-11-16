/**
 * @file tcp_server.c
 * @author MK
 * @brief 
 * @version 0.1
 * @date 16-11-2024
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "tcp_server.h"

void printClientIP(server_data_t *data)
{
    char clientIP[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(data->clientAddr.sin_addr), clientIP, INET_ADDRSTRLEN);
    printf("Client IP Address: %s\n", clientIP);
}

void serverInit(server_data_t *data)
{
    // Step 1: Initialize Winsock
    printf("Initialize Winsock...\n");
    if(WSAStartup(MAKEWORD(2,2), &(data->wsaData)) != 0)
    {
        printf("WSAStartup Failed!\n");
        exit(1);
    }

    // Step 2: Create a server socket
    printf("Create a server socket...\n");
    data->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(data->serverSocket == INVALID_SOCKET)
    {
        printf("Socket creation failed with error: %d\n", WSAGetLastError());
        WSACleanup();
        exit(1);
    }

    // Step 3: Bind the socket to an IP address and port
    printf("Bind the socket...\n");
    memset(&data->serverAddr, 0, sizeof(data->serverAddr)); // Clear the memory for serverAddr
    data->serverAddr.sin_family = AF_INET;
    data->serverAddr.sin_addr.s_addr = INADDR_ANY; // Listen on any available network interface
    data->serverAddr.sin_port = htons(PORT);

    if(bind(data->serverSocket, (struct sockaddr*)&(data->serverAddr), sizeof(data->serverAddr)) == SOCKET_ERROR)
    {
        printf("Bind failed with error: %d\n", WSAGetLastError());
        closesocket(data->serverSocket);
        WSACleanup();
        exit(1);
    }


    // Step 4: Listen for incoming connections
    printf("Listen for incoming connections...\n");
    if(listen(data->serverSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        printf("Listen failed with error: %d\n", WSAGetLastError());
        closesocket(data->serverSocket);
        WSACleanup();
        exit(1);
    }
    printf("Server is lisenting on port %d...\n", PORT);

}

void serverCleanup(server_data_t *data)
{
    
	// Step 7: Clean up resources
    printf("Clean up resources... :)\n");
    closesocket(data->clientSocket);
    closesocket(data->serverSocket);
    WSACleanup();
}