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
#define PORTNUMBER 12345
#define BUFFER_SIZE 256 

// Main executable
// Server side
int main(){
	int server_fd = socket(AF_INET, SOCK_STREAM, 0); // Create server fd to listen for incoming communications // Domain(ADDRESS FAMILY --> INTERNET), Type(SOCK_STREAM/SOCK_DGRAM --> TCP/UDP), Protocol(0)
	int new_socket;// New file descriptor on client connection
	int valread; // Number of bytes recieved from the client

	struct sockaddr_in server_address; // Struct to store server addresses(IP NUMBER // PORT NUMBER) when using IPV4
	int address_len = sizeof(server_address); // Store the size of the struct
	char buffer[BUFFER_SIZE] = {0}; // Store message data sent... All zero ensure garbage collection using the null terminator when buffer size not reached

	// If socket creation fails!
	if(server_fd == -1){
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
	if(bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0){
		perror("Failed to bind server socket to configured address!\n");
		exit(EXIT_FAILURE);
		
	}

	// On success listen for connections --> syntax listen(sockfd, backlog) --> On error returns negative int, backlog(Maximum number of connections) 
	if(listen(server_fd, 3)){
		perror("Failed to listen on binded address!\n");
		exit(EXIT_FAILURE);
		
	}

	printf("Server listening on port: %d\n", PORTNUMBER);

	// Server runnning now accept connections
	

	
	

	return 0; // No error
}

