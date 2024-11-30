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
    int status = 0;

    memset(buffer, 0, buf_len);

    /* Step 1-4 */
    serverInit(&data);

    serverAcceptConn(&data, &clientAddrSize);

    printClientIP(&data);

    while(1)
    {
        status = serverRxAndEcho(&data, buffer, buf_len);
        if(status != 0)
        {
            break;
        }
    }

    /* Step 7 */
    serverCleanup(&data);

    return 0;
}