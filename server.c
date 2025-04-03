#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>


/* Steps
1. Create socket for communication
2. Bind the socket to a port
3. Listen for incoming connections
4. Accept the connection
5. Read the request
6. Send the response
7. Close the connection
*/


// Main entry point
int main(){

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <unistd.h>
	#include <arpa/inet.h>
	#include <sys/socket.h>
	
	#define PORT 8080
	#define BUFFER_SIZE 1024

int main(){
		int server_fd, new_socket, valread;
	    struct sockaddr_in address;
	    int opt = 1;
	    int addrlen = sizeof(address);
	    char buffer[BUFFER_SIZE] = {0};
	
	    // Create socket
	    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
	        perror("socket failed");
	        exit(EXIT_FAILURE);
	    }
	
	    // Set socket options
	    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
	        perror("setsockopt");
	        exit(EXIT_FAILURE);
	    }
	
	    address.sin_family = AF_INET;
	    address.sin_addr.s_addr = INADDR_ANY;
	    address.sin_port = htons(PORT);
	
	    // Bind socket to address
	    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
	        perror("bind failed");
	        exit(EXIT_FAILURE);
	    }
	
	    // Listen for connections
	    if (listen(server_fd, 3) < 0) {
	        perror("listen");
	        exit(EXIT_FAILURE);
	    }
	
	    // Accept connection
	    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
	        perror("accept");
	        exit(EXIT_FAILURE);
	    }
	
	    // Receive and send data
	    while ((valread = read(new_socket, buffer, BUFFER_SIZE)) > 0) {
	        printf("Received: %s", buffer);
	        send(new_socket, buffer, strlen(buffer), 0);
	        memset(buffer, 0, BUFFER_SIZE); // clear the buffer.
	    }
	
	    // Close sockets
	    close(new_socket);
	    close(server_fd);
	    return 0;
	}
}
