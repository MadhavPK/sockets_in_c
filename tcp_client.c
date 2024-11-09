/**
 * @file tcp_client.c
 * @author MK
 * @brief Client side program
 * gcc .\tcp_client.c -o .\tcp_client.exe -lws2_32
 * @version 0.1
 * @date 2024-11-09
 * @source https://chatgpt.com/share/672f294a-b928-8007-9092-42e8d0044f72
 * @copyright Copyright (c) 2024
 * 
 */
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

// #pragma comment(lib, "ws2_32.lib")  // Linik with Winsock library

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080
#define BUFFER_SIZE 1024

int main(int argc, char const* argv[])
{
    WSADATA wsaData;
    SOCKET clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];
    const char* message = "Hello Server!";

    // Step 1: Initialize Winsock
    printf("Initialize Winsock...\n");
    if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
    {
        printf("WSAStartup Failed!\n");
        return 1;
    }

    // Step 2: Create a client socket
    printf("Create client socket...\n");
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(clientSocket == INVALID_SOCKET)
    {
        printf("Socket creation failed with error: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Step 3: Specify the server address and port
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr);

    // Step 4: Connect to the server
    if(connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        printf("Connection to server failed with error: %d\n", WSAGetLastError());
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    printf("Connected to server at %s:%d\n", SERVER_IP, SERVER_PORT);

    // Step 5: Send a message to the server
    printf("Send message...\n");
    if(send(clientSocket, message, strlen(message), 0) == SOCKET_ERROR)
    {
        printf("Send failed with error: %d\n", WSAGetLastError());
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    printf("Sent message: %s\n", message);

    // Step 6: Receive the server's response
    int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
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

    // Step 7: Clean up resources
    printf("Clean up resources... :)\n");
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}