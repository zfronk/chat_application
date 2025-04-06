# Simple C Chat Server

This is a basic server-side application written in C that listens for incoming connections on a specified port, intended as a foundation for a chat application.

## Features

* Creates a socket for network communication.
* Binds the socket to a configured IP address (listening on all available interfaces) and port number.
* Listens for incoming connections.

## Getting Started

### Prerequisites

* A C compiler (like GCC)
* A system that supports socket programming (most modern operating systems)

### Compilation

1.  Save the provided C code as `chat-server.c`.
2.  Open your terminal and navigate to the directory where you saved the file.
3.  Compile the code using GCC:
    ```bash
    gcc chat-server.c -o chat_server.exe
    ```
    *(Note for Windows users: The executable might be named `chat_server.exe`. On Linux/macOS, it will typically be `chat_server` unless explicitly specified.)*

### Running the Server

1.  In the same terminal, execute the compiled program:
    ```bash
    ./chat_server.exe
    ```
    *(On Linux/macOS, it would likely be `./chat_server`)*
2.  The server will start and print a message indicating that it is listening on the configured port (default is 12345).

## Usage

Currently, this server only sets up the listening socket. It does not yet accept or handle incoming connections. To make it a functional chat server, you would need to add code to:

1.  **Accept incoming connections:** Use the `accept()` system call.
2.  **Receive messages from clients:** Use the `recv()` system call.
3.  **Broadcast messages:** Implement logic to send received messages to all connected clients.
4.  **Send messages to specific clients (optional):** Add features for private messaging.
5.  **Close connections:** Use the `close()` system call when clients disconnect.
6.  **Manage multiple clients:** Implement a mechanism to handle multiple concurrent client connections (e.g., using threads, processes, or asynchronous I/O).

## Code Explanation

### Header Files

* `stdio.h`: For standard input/output functions like `printf` and `perror`.
* `stdlib.h`: For general utility functions like `exit`.
* `string.h`: For string manipulation functions like `strlen`.
* `stdbool.h`: For using boolean data types (`bool`, `true`, `false`).
* `time.h`: Included but not currently used in this version.
* `unistd.h`: For POSIX operating system API functions like `close`.
* `sys/socket.h`: For socket programming functions and structures.
* `netinet/in.h`: For internet address family (IPv4) specific structures.
* `arpa/inet.h`: For functions to convert IP addresses between text and binary.

### Preprocessor Macros

* `#define PORTNUMBER 12345`: Defines the port number the server will listen on.
* `#define BUFFER_SIZE 256`: Defines the maximum size of the data buffer (used for potential future receiving of messages).

### `main` Function

1.  **Socket Creation:**
    ```c
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    ```
    Creates a socket file descriptor (`server_fd`) for listening to incoming TCP connections over the internet (IPv4).

2.  **Error Handling (Socket Creation):**
    ```c
    if(server_fd == -1){
        perror("Socket to server creation failed!\n");
        exit(EXIT_FAILURE);
    }
    ```
    Checks if socket creation failed and exits if it did, printing an error message.

3.  **Success Message (Socket Creation):**
    ```c
    printf("Socket to server created successfuly!\n");
    ```
    Prints a confirmation message upon successful socket creation.

4.  **Address Configuration:**
    ```c
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORTNUMBER);
    int address_len = sizeof(server_address);
    ```
    Configures the server's address information:
    * `sin_family`: Sets the address family to IPv4.
    * `sin_addr.s_addr`: Sets the IP address to listen on all available network interfaces.
    * `sin_port`: Sets the port number to listen on, converting it to network byte order using `htons()`.
    * `address_len`: Stores the size of the `server_address` structure.

5.  **Binding the Socket:**
    ```c
    if(bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0){
        perror("Failed to bind server socket to configured address!\n");
        exit(EXIT_FAILURE);
    }
    ```
    Associates the created socket (`server_fd`) with the configured server address.

6.  **Listening for Connections:**
    ```c
    if(listen(server_fd, 3)){
        perror("Failed to listen on binded address!\n");
        exit(EXIT_FAILURE);
    }
    ```
    Starts listening for incoming connection requests on the bound socket. The `backlog` parameter (3 in this case) specifies the maximum number of pending connections the system can queue.

7.  **Listening Confirmation:**
    ```c
    printf("Server listening on port: %d\n", PORTNUMBER);
    ```
    Prints a message indicating that the server is now listening.

## Next Steps

To make this a functional chat server, the following steps need to be implemented:

* **Accepting Connections:** Implement a loop using the `accept()` system call to accept incoming client connections. This will create a new socket file descriptor for each client.
* **Handling Client Communication:** For each connected client, you'll need to:
    * **Receive messages:** Use `recv()` to read messages sent by the client.
    * **Implement chat logic:** Handle the received messages (e.g., broadcasting).
    * **Send messages:** Use `send()` to send messages to connected clients.
* **Managing Multiple Clients:** Decide on a mechanism to handle multiple concurrent client connections.
* **Closing Connections:** Properly close client sockets using `close()` when clients disconnect.

## Contributing

Feel free to contribute to this basic chat server by adding the missing functionalities or improving the existing code.

## License

[Your License Here (e.g., MIT License)]
