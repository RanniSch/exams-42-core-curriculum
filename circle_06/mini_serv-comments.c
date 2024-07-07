#include <sys/socket.h> 		// socket(), send(), bind(), listen(); libary for socket web server
#include <stdio.h>				// sprintf(), NULL (This macro is the value of a null pointer constant)
#include <unistd.h>				// write()
#include <string.h>				// bzero()
#include <stdlib.h>				// atoi(), exit(), NULL
#include <netinet/in.h>			// Internet Protocol family; defines the sockaddr_in structure
#include <netdb.h>				// definitions for network database operations; it may make available the type in_addr_t as defined in <netinet/in.h>

// s_client = name if the struct, t_client = data type of the struct
typedef struct s_client			// struct s_client is a structure definition. A user-defined data type that allows grouping variables of different types together.
{
	int id;						// This member is an integer and can be used to store any integer value related to the 'client'.
	/** or [100000] if not passing **/
	char msg[1024];				// This member is an array of characters (a string) with a size of 1024 characters: Maximum number of client connections allowed
}				t_client;	// typedef struct creates a type alias t_client for the structure s_client, so instead of writing struct s_client to declare a variable of this structure type, you can simply write t_client.

t_client	clients[1024];				// Array to store client socket descriptors								

// fd_set is a struct representing a filedescriptor; File descriptor sets for tracking socket activity; File descriptor provide low-level interface to input and output operations.
fd_set		writeFds;
fd_set		readFds;
fd_set		active;
int 		fdMax = 0;
int			idNext = 0;				// Identifier for the next client connection

// Buffer for storing received messages
char		bufferRead[120000], bufferWrite[120000];				// Size of the buffer used for message exchange

// takes care of all error management
void	ft_error(char *string)
{
	if (string)
		write(2, string, strlen(string));
	else
		write(2, "Fatal error", strlen("Fatal error"));
	write(2, "\n", 1);
	exit(1);										// Terminate the program with a non-zero status code	
}

// This part is reusing the send utility for each section
void	send_all(int fd)
{
	for (int i = 0; i <= fdMax; i++)
		// FD_ISSET returns a non-zero value if the bit for the file descriptor i is set in the file descriptor set pointed to by writeFds, and 0 otherwise
		if (FD_ISSET(i, &writeFds) && i != fd)		// send the message to everyone but fd = connfd, because connfd is the one sending it
			// send() shall initiate transmission of a message from the specified socket to its peer. It sends a message only when the socket is connected
			send(i, bufferWrite, strlen(bufferWrite), 0);	// i: Specifies the socket file descriptor; bufferWrite: Points to the buffer containing the message to send; Specifies the length of the message in bytes; type of message transmission
}

int main(int argc, char **argv)
{
	if (argc != 2)									// Check if the number of command line arguments is incorrect
		ft_error("Wrong number of arguments");		// Print an error message with ft_error

	// Create the server socket/create an endpoint for communication
	// AF_INET: Specifies the communications domain in which a socket is to be created (we want to connect hosts through ipv4)
	// SOCK_STREAM: Specifies the type of socket to be created (we use TCP/IP protocol for communication)
	// 0: Specifies a particular protocol to be used with the socket (it's 0 for TCP/IP)
	int socketfd = socket(AF_INET, SOCK_STREAM, 0);		// Create a socket with IPv4 addressing and TCP protocol and returns the new socketfd or -1 for error
	if (socketfd < 0)				// Check if socket creation failed			
		ft_error(NULL);				// Print an error message with ft_error
	
	// Initialise the active sockets set
	FD_ZERO(&active);				// Clear the set of active sockets, because it sets the active (back) to zero. 'FD_ZERO' initializes the file descriptor set active to have zero bits for all file descriptors.
	bzero(&clients, sizeof(clients));	// initialize the t_clients struct clients with all 0's to prevent certain segfaults, by placing in the sizeof 'clients' zero-valued bytes in the area pointed to by '&clients'
	fdMax = socketfd;				// update fdMax to our newly created socket (Variable to track the maximum socket descriptor)
	FD_SET(socketfd, &active);		// Add the newly created server socket to the set of active. 'FD_SET' sets the bit for the file descriptor socketfd in the file descriptor set active.

	// Set up the server address
	// sockaddr_in structure is used to store addresses for the Internet protocol family
	struct sockaddr_in  serveraddr;		// struct sockaddr_in is a datastructure for information about an Ip-address (Structure to hold the server address)
	socklen_t           len;			// socklen_t: is an int specifying the size of a sockaddr_ -> from the sys/socket.h libary
	bzero(&serveraddr, sizeof(serveraddr));	// set everything to zero in the struct to prevent segfaults by placing in the sizeof 'serveraddr' zero-valued bytes in the area pointed to by '&serveraddr'

	// the sockaddr_in structure includes the members: sin_family, sin_addr, sin_port
	// s_addr is member of the in_addr structure which is an unsigned integral type of exactly 32 bits
	serveraddr.sin_family = AF_INET;		// Set address family to IPv4
	serveraddr.sin_addr.s_addr = htonl(2130706433);		// Set the IP address to localhost. Given in main, is 127.0.0.1 in network bytes; htonl converts a 32bit to network bytes. Instead INADDR_LOOPBACK could be an option
	serveraddr.sin_port = htons(atoi(argv[1]));		// Set the port number from the command line argument and converts a 16bit to network bytes short

	// bind the newly created server socket to the IP (to the specified address)/ bind a name to a socket
	if ((bind(socketfd, (const struct sockaddr *) &serveraddr, sizeof(serveraddr))) < 0)	// socketfd: Specifies the file descriptor of the socket to be bound; Points to a sockaddr structure containing the address to be bound to the socket; length of the sockaddr structure
		ft_error(NULL);		// if binding fails: Print an error message with ft_error

	// Putting the socket into listening mode, to listen for incoming connections. Now its waiting for a client to connect
	// 10 defines the max. amount of clients that can be in queue waiting for a connection to the server.
	if (listen(socketfd, 10) < 0)		// 10 are 'MAX_CLIENTS' (others have defined it to 128)
		ft_error(NULL);		// if listening fails: Print an error message with ft_error

	while(1)
	{
		// Wait for activity on the sockets
		readFds = writeFds = active;				// Copy the active sockets set for use with select()

		// select(): indicates which of the specified file descriptors is ready for reading, ready for writing, or has an error condition pending
		// select(highest possible number of fds to check, set of fds that could be possibly reading, set of fds that could possibly be writing, NULL, NULL)
		// select() can only monitor filedescriptors lower than whats specified by fdMax + 1
		// readfds and writefds: are fildescriptor sets that contain the fildescriptors that being monitored to check if they are ready for the corresponding action (reading or writing)
		// returns -1 on error or the number of fds that are in the fds-sets and are performing an operation (read,write or execption)
		if (select(fdMax + 1, &readFds, &writeFds, NULL, NULL) < 0)	// fdMax + 1: range of file descriptors to be tested; &readFds: on input specifies the file descriptors to be checked for being ready to read, and on output indicates which file descriptors are ready to read; same for &writeFds; 
			continue;		// if select() fails: jumps directly to while(1), so no break, but the input is ignored. 
		
		// Check each socket for activity
		for(int fdI = 0; fdI <= fdMax; fdI++)	// go thru all fds we have and check if one of them is being used for read-opertion. If it is and it is also the sockfd then
		{
			if (socketfd < 0)
				ft_error(NULL);
			// FD_ISSET: checks if the fd is in the fd-set: Returns a non-zero value if the bit for the file descriptor fdI is set in the file descriptor set pointed to by readFds, and 0 otherwise
			if (FD_ISSET(fdI, &readFds) && fdI == socketfd)	// a new client enters (fdI == socketfd checks if the activity is on the server socket)
			{
				// This is where we accept connections; new client connection
				// accept() returns a new sockfd for the connection or -1 on error
				int connfd = accept(socketfd, (struct sockaddr *)&serveraddr, &len);	// Accept 'accept()' a new client connection. It extracts the first connection request from the queue of the input socket
				if (connfd < 0)
					continue;		// if accepting fails: jumps directly to for(int fdI = 0; fdI <= fdMax; fdI++), so no break, but the input is ignored.
				
				// Add the new client socket to the active set
				fdMax = connfd > fdMax ? connfd : fdMax;		// Update the maximum socket descriptor; if connfd > fdMax -> connfd is assigned to fdMax, else fdMax
				clients[connfd].id = idNext++;		// Store the client socket for future reference; Add the client socket to the array	
				FD_SET(connfd, &active);		// Add the client socket to the set of active sockets
				
				// Send a welcome message to the client; sprintf() sends formatted output to a string
				sprintf(bufferWrite, "server: client %d just arrived\n", clients[connfd].id);		// Prepare the welcome message
				send_all(connfd);		// Send the welcome message to the client with send_all()
				break;
			}
			// when its not sockfd but another client
			if (FD_ISSET(fdI, &readFds) && fdI != socketfd)	// (if the if before does not apply: if the activity is not on the server socket)
			{
				// Receive a message from a connected socket (Data received from a client)
				// recv(): reads data from a socket and returns the number of bytes read or -1 on error or 0 if connections is closed
				// 65536: common max for packet size of network protocols (Instead 65536 sizeof(bufferRead) - 1 could be an option)
				int res = recv(fdI, bufferRead, 65536, 0);	// fdI: Specifies the socket file descriptor; Points to a buffer where the message should be stored; Specifies the length in bytes of the buffer pointed to by the buffer argument; Specifies the type of message reception
				if (res <= 0)
				{
					// Client disconnected
					sprintf(bufferWrite, "server: client %d just left\n", clients[fdI].id);		// Prepare the disconnection message
					send_all(fdI);				// Send the disconnecion message to the client with send_all()
					
					// Close the socket and remove it from the active set
					FD_CLR(fdI, &active);		// Remove the client socket from the set of active sockets. It clears the fd from the fd-set
					close(fdI);		// Close the client socket by closing the fd
					break;
				}
				else
				{
					for (int i = 0, j = strlen(clients[fdI].msg); i < res; i++, j++)
					{
						clients[fdI].msg[j] = bufferRead[i];
						if (clients[fdI].msg[j] == '\n')
						{
							// Broadcast the received message to all other clients
							clients[fdI].msg[j] = '\0';		// Null-terminate the received message
							sprintf(bufferWrite, "client %d: %s\n", clients[fdI].id, clients[fdI].msg);		// Add client identifier to the message
							send_all(fdI);		// // Send the message to other clients???
							bzero(&clients[fdI].msg, strlen(clients[fdI].msg));
							j = -1;
						}
					}
					break;
				}
			}
		}
	}
}
