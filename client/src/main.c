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
    const char* welcome_message = "Hello from NoobMaster!";
    int welcome_message_len = strlen(welcome_message);
    /* Step 1 - 4 */
    clientInit(&data);

    /* Step 5 */
    clientSend(&data, welcome_message, welcome_message_len);
    
    /* Step 6 */
    clientRecv(&data, buffer);

    /* Step 7 */
    clientCleanup(&data);

    return 0;
}