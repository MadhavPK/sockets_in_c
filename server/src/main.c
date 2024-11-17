/**
 * @file main.c
 * @author MK
 * @brief Server side C program
 * gcc .\tcp_server.c -o .\tcp_server.exe -lws2_32 -liphlpapi -static
 * @version 0.1
 * @date 2024-11-09
 * @source https://chatgpt.com/share/672f294a-b928-8007-9092-42e8d0044f72
 * @copyright Copyright (c) 2024
 * 
 */

// #pragma comment(lib, "ws2_32.lib") // link with Winsock library

#include "tcp_server.h"

int main(int argc, char const* argv[])
{
    server_data_t data;
    char buffer[BUFFER_SIZE];
    uint16_t buf_len = sizeof(buffer);
    int clientAddrSize = sizeof(data.clientAddr);

    /* Step 1-4 */
    serverInit(&data);

    // Step 5: Accept a client connection
    printf("Accept a client connection...\n");
    data.clientSocket = accept(data.serverSocket, (struct sockaddr*)&(data.clientAddr), &clientAddrSize);
    if(data.clientSocket == INVALID_SOCKET)
    {
        printf("Listen failed with error: %d\n", WSAGetLastError());
        closesocket(data.serverSocket);
        WSACleanup();
        return 1;
    }

    printf("Client connected...\n");
    printClientIP(&data);

    // Step 6: Receive and echo messages
    while(1)
    {
        int bytesReceived = recv(data.clientSocket, buffer, BUFFER_SIZE, 0);
        if(bytesReceived > 0)
        {
            buffer[bytesReceived] = '\0'; // Null-terminate the received data
            printf("Received message: %s\n", buffer);

            // Echo the message back to the client
            memset(buffer, 0, buf_len);
            strcpy(buffer, "Hello from Davinci!");
            send(data.clientSocket, buffer, buf_len, 0);
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

    /* Step 7 */
    serverCleanup(&data);

    return 0;
}