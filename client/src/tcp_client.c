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
    uint16_t server_port = 8080;
    char server_ip[16] = "127.0.0.1";

    //                  Step 1: Initialize Winsock
    printf("Initialize Winsock...\n");
    if(WSAStartup(MAKEWORD(2,2), &(data->wsaData)) != 0)
    {
        printf("WSAStartup Failed!\n");
        exit(1);
    }

    //                  Step 2: Create a client socket
    printf("Create client socket...\n");
    data->clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(data->clientSocket == INVALID_SOCKET)
    {
        printf("Socket creation failed with error: %d\n", WSAGetLastError());
        WSACleanup();
        exit(1);
    }

    //                  Step 3: Specify the server address and port
    printf("Enter Server Port Number: ");
    scanf("%hd", &server_port);
    printf("\n");

    printf("Enter Server IP address: ");
    if(scanf("%16s", server_ip) <= 0)  // Limit the input size to avoid buffer overflow
    {
        // Remove the trailing newline character if present
        server_ip[strcspn(server_ip, "\n")] = '\0';
    }
    // Check if the IP is valid
    if(strlen(server_ip) <= 6)
    {
        printf("ERROR: wrong IP address: %s\n", server_ip);
        exit(1);

    }
    
    printf("You entered: %s\n", server_ip);

    data->serverAddr.sin_family = AF_INET;
    data->serverAddr.sin_port = htons(server_port);
    inet_pton(AF_INET, server_ip, &(data->serverAddr.sin_addr));

    // Step 4: Connect to the server
    if(connect(data->clientSocket, (struct sockaddr*)&(data->serverAddr), sizeof(data->serverAddr)) == SOCKET_ERROR)
    {
        printf("Connection to server failed with error: %d\n", WSAGetLastError());
        closesocket(data->clientSocket);
        WSACleanup();
        exit(1);
    }
    printf("Connected to server at %s:%d\n", server_ip, server_port);

}

void clientCleanup(client_data_t *data)
{
    //                  Step 7: Clean up resources
    printf("Clean up resources... :)\n");
    closesocket(data->clientSocket);
    WSACleanup();
}

void clientSend(client_data_t *data, const char* msg, int msg_len)
{
    // Step 5: Send a message to the server
        printf("Send message...\n");
        if(send(data->clientSocket, msg, msg_len, 0) == SOCKET_ERROR)
        {
            printf("Send failed with error: %d\n", WSAGetLastError());
            closesocket(data->clientSocket);
            WSACleanup();
            exit(1);
        }
        printf("Sent message: %s\n", msg);
}

void clientRecv(client_data_t *data, char *buffer)
{
    // Step 6: Receive the server's response
    int bytesReceived = recv(data->clientSocket, buffer, BUFFER_SIZE, 0);
    if(bytesReceived > 0)
    {
        buffer[bytesReceived] = '\0'; // Null-terminate the received data
        printf("Received response from server: %s\n", buffer);
    } else if(bytesReceived == 0)
    {
        printf("Server closed the connection\n");
    } else
    {
        printf("recv failed with error: %d\n", WSAGetLastError());
    }
}