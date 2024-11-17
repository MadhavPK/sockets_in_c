/**
 * @file main.c
 * @author MK
 * @brief Client side program
 * gcc .\tcp_client.c -o .\tcp_client.exe -lws2_32
 * @version 0.1
 * @date 2024-11-09
 * @source https://chatgpt.com/share/672f294a-b928-8007-9092-42e8d0044f72
 * @copyright Copyright (c) 2024
 * 
 */

// #pragma comment(lib, "ws2_32.lib")  // Link with Winsock library

#include "tcp_client.h"

int main(int argc, char const* argv[])
{
    client_data_t data;
    char buffer[BUFFER_SIZE];
    const char* message = "Hello from NoobMaster!";

    /* Step 1 - 4 */
    clientInit(&data);

    // Step 5: Send a message to the server
    printf("Send message...\n");
    if(send(data.clientSocket, message, strlen(message), 0) == SOCKET_ERROR)
    {
        printf("Send failed with error: %d\n", WSAGetLastError());
        closesocket(data.clientSocket);
        WSACleanup();
        return 1;
    }
    printf("Sent message: %s\n", message);

    // Step 6: Receive the server's response
    int bytesReceived = recv(data.clientSocket, buffer, BUFFER_SIZE, 0);
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

    /* Step 7 */
    clientCleanup(&data);

    return 0;
}