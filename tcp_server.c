/**
 * @file tcp_server.c
 * @author MK
 * @brief Server side C program
 * gcc .\tcp_server.c -o .\tcp_server.exe -lws2_32
 * @version 0.1
 * @date 2024-11-09
 * @source https://chatgpt.com/share/672f294a-b928-8007-9092-42e8d0044f72
 * @copyright Copyright (c) 2024
 * 
 */
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

// #pragma comment(lib, "ws2_32.lib") // link with Winsock library

#define PORT        8080
#define BUFFER_SIZE  1024

void printClientIP(struct sockaddr_in *clientAddr)
{
    char clientIP[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(clientAddr->sin_addr), clientIP, INET_ADDRSTRLEN);
    printf("Client IP Address: %s\n", clientIP);
}

int main(int argc, char const* argv[])
{
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    char buffer[BUFFER_SIZE];
    int clientAddrSize = sizeof(clientAddr);

    // Step 1: Initialize Winsock
    printf("Initialize Winsock...\n");
    if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
    {
        printf("WSAStartup Failed!\n");
        return 1;
    }

    // Step 2: Create a server socket
    printf("Create a server socket...\n");
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSocket == INVALID_SOCKET)
    {
        printf("Socket creation failed with error: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Step 3: Bind the socket to an IP address and port
    printf("Bind the socket...\n");
    memset(&serverAddr, 0, sizeof(serverAddr)); // Clear the memory for serverAddr
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY; // Listen on any available network interface
    serverAddr.sin_port = htons(PORT);

    if(bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        printf("Bind failed with error: %d\n", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }


    // Step 4: Listen for incoming connections
    printf("Listen for incoming connections...\n");
    if(listen(serverSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        printf("Listen failed with error: %d\n", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    printf("Server is lisenting on port %d...\n", PORT);

    // Step 5: Accept a client connection
    printf("Accept a client connection...\n");
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrSize);
    if(clientSocket == INVALID_SOCKET)
    {
        printf("Listen failed with error: %d\n", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    printf("Client connected...\n");
    printClientIP(&clientAddr);

    // Step 6: Receive and echo messages
    while(1)
    {
        int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
        if(bytesReceived > 0)
        {
            buffer[bytesReceived] = '\0'; // Null-terminate the received data
            printf("Received message: %s\n", buffer);

            // Echo the message back to the client
            send(clientSocket, buffer, bytesReceived, 0);
        } else if(bytesReceived == 0)
        {
            printf("Client disconnected...\n");
            break;
        } else
        {
            printf("recv failed with error: %d\n", WSAGetLastError());
            break;
        }
    }

	// Step 7: Clean up resources
    printf("Clean up resources... :)\n");
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();
    return 0;
}