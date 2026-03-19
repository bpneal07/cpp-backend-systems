#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


int main() {
	std::cout<< "Backend systems project initialized." << std::endl;
	// Choose a port
	const int port = 8080; // This is the port the server will listen on

	// Create a socket
	int server_fd = socket(AF_INET, SOCK_STREAM, 0); // This asks the OS to create a socket
	 												  // The return value is int server_fd "file descriptor"
													  // AF_INET: use IPv4 addresses
													  // SOCK_STREAM: use a stream socket; For internet socket, this means TCP
													  // 0: use the default protocol for this socket type Linux understands it's TCP
	// Check if Socket Creation Failed
	if (server_fd < 0){
		std::cerr <<"Failed to create socket\n"; // If socket() fails print an error and exit the program
		return 1;
	}
	 
	//Create the server address structure
	sockaddr_in server_address{}; //Creates a variable that holds the address information for the server

	//Set the address family
	server_address.sin_family = AF_INET; // IPv4 address that matches socket type;

	//Set the IP address
	server_address.sin_addr.s_addr = INADDR_ANY; //Listen on all available network interfaces

	//Set the port
	server_address.sin_port = htons(port); //Network code expects values in network byte order
										   //Host to network short converts machine's local rep into format expected by networking code

	//Bind the socket 
	if (bind(server_fd, reinterpret_cast<sockaddr*>(&server_address), sizeof(server_address)) < 0){
		std::cerr << "Failed to bind socket\n";
		close(server_fd);
		return 1;
	}
	// bind: attach this socket to this address and port
	// Before bind(), the socket exists, but it is not tied to a specific listening port.
	// After bind(), the socket is associated with port 8080

	//Start listening
	if (listen(server_fd, 5) < 0){
		std::cerr << "Failed to listen on socket\n";
		close(server_fd);
		return 1;
	}

	return 0;

}
