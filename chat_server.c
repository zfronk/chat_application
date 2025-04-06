#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <sys/socket.h>
#include <netinet/in.h>

// Macro components
#define PORTNUMBER 12345
#define BUFFER_SIZE 256 

// Main executable
// Server side
int main(){
	int server_fd = socket(AF_INET, SOCK_STREAM, 0); // Create server fd to listen for incoming communications // Domain(ADDRESS FAMILY --> INTERNET), Type(SOCK_STREAM/SOCK_DGRAM --> TCP/UDP), Protocol(0)
	int new_socket;// New fd on client connection
	int valread; // Number of bytes recieved from the client

	struct sockaddr_in address; // Struct to store server addresses(IP NUMBER // PORT NUMBER)
	int address_len = sizeof(address); // Store the size of the struct
	char buffer[BUFFER_SIZE] = {0}; // Store message data sent... All zero ensure garbage collection using the null terminator when buffer size not reached

	// If socket creation fails!
	if(server_fd == -1){
		perror("Socket to server creation failed!\n");
		exit(EXIT_FAILURE);
		
	}

	// Success message
	printf("Socket to server created successfuly!\n");

	// Configure the address of the server
	address.sin_family = AF_INET; // Address family i use IPV4 
	address.sin_addr.s_addr = INADDR_ANY; // Listen for connection on all available network interfaces
	address.sin_port = htons(PORTNUMBER); // Convert the port number to network byte order

	
	

	return 0; // No error
}

