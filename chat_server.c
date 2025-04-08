#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h> 
#include <unistd.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// Preprocessor macro components
#define PORTNUMBER 8080
#define BUFFER_SIZE 256 

// Main executable
// Server side
int main(){
	int server_socket = socket(AF_INET, SOCK_STREAM, 0); // Create server fd to listen for incoming communications // Domain(ADDRESS FAMILY --> INTERNET), Type(SOCK_STREAM/SOCK_DGRAM --> TCP/UDP), Protocol(0)
	int client_socket;// New file descriptor on client connection
	int valread; // Number of bytes recieved from the client

	struct sockaddr_in server_address; // Struct to store server addresses and details -> Port, Address Family
	struct sockaddr_in client_address; // Struct to store client addresses and details
	
	int server_address_len = sizeof(server_address); // Store the size of the server address
	int client_address_len = sizeof(client_address); // Store the size of the client address

	char buffer[BUFFER_SIZE] = {0}; // Store message data sent... All zero ensure garbage collection using the null terminator when buffer size not reached

	// If socket creation fails!
	if(server_socket == -1){
		perror("Socket to server creation failed!\n");
		exit(EXIT_FAILURE);
		
	}

	// Success message
	printf("Socket to server created successfuly!\n");

	// Configure the address of the server
	server_address.sin_family = AF_INET; // Address family i use IPV4 
	server_address.sin_addr.s_addr = INADDR_ANY; // Listen for connection on all available network interfaces
	server_address.sin_port = htons(PORTNUMBER); // Convert the port number to network byte order

	// Bind the server to the address.. Bind takes pointer address...
	if(bind(server_socket, (struct sockaddr *)&server_address, server_address_len) < 0){
		perror("Failed to bind server socket to configured address!\n");
		exit(EXIT_FAILURE);
		
	}

	// On success listen for connections --> syntax listen(sockfd, backlog) --> On error returns negative int, backlog(Maximum number of connections) 
	if(listen(server_socket, 1) < 0){
		perror("Failed to listen on binded address!\n");
		exit(EXIT_FAILURE);
		
	}

	// If successfull!
	printf("Server listening on port: %d\n", PORTNUMBER);

	printf("Waiting for client to connect...\n");

	// Server runnning now accept connections
	if((client_socket = accept(server_socket, (struct sockaddr *)&client_address, (socklen_t *)&client_address_len)) < 0){
		perror("Failed to accept client!\n");
		close(server_socket);
		exit(EXIT_FAILURE);
		
	}

	printf("Client connected succesfully!\n");

	bool stay_connected = true; // Boolen to act as a switch

	while(stay_connected){
		memset(buffer, 0, BUFFER_SIZE); // Clear the buffer on loop start
		int read_bytes = read(client_socket, buffer, BUFFER_SIZE); // Read bytes from the client!

		if(read_bytes <= 0){ // If bytes read less than 0 or zero either host unreachable...
			perror("Error reading bytes from client!\n");
			close(client_socket);
			close(server_socket);
			exit(EXIT_FAILURE);
			stay_connected = false;
			
		}

		printf("Client: %s", buffer);

		memset(buffer, 0, BUFFER_SIZE); // Clear the buffer input!
		printf("You: ");
		fgets(buffer, BUFFER_SIZE, stdin); // Get server operater input!

		send(client_socket, buffer, strlen(buffer), 0); // Send server operater message

		

		
		
	}
	

	
	

	return 0; // No error
}

