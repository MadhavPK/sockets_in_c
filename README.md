# Sockets in C
> **NOTE:**<br>
> Here I am using `winsock2` on windows. This codes works only on Windows.
## Environment
1. VSCode IDE
2. MSYS2
   ```
    pacman -S --needed base-devel mingw-w64-x86_64-toolchain
   ```
   This will install the `gcc` and `make`.
3. You will have to add these to `PATH` environment variable
   1. `C:\msys64\usr\bin`
   2. `C:\msys64\mingw64\bin`

## Server brief
Step 1: Initialize Winsock

Step 2: Create a server socket

Step 3: Bind the socket to an IP address and port

Step 4: Listen for incoming connections

Step 5: Accept a client connection

Step 6: Receive and echo messages

Step 7: Clean up resources


## Client brief
Step 1: Initialize Winsock

Step 2: Create a client socket

Step 3: Specify the server address and port

Step 4: Connect to the server

Step 5: Send a message to the server

Step 6: Receive the server's response

Step 7: Clean up resources

## Reference
[ChatGPT](https://chatgpt.com/share/672f294a-b928-8007-9092-42e8d0044f72)