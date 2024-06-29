#include <sys/socket.h> 
#include <stdio.h>
#include <unistd.h>
#include <string.h>				// bzero()
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>

typedef struct s_client
{
	int id;
	char msg[1024];				// Maximum number of client connections allowed
}				t_client;

t_client	clients[1024];				// Array to store client socket descriptors								

// File descriptor sets: File descriptor sets for tracking socket activity
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

// This part is reusing the send utility for each section.
void	send_all(int fd)
{
	for (int i = 0; i <= fdMax; i++)
		if (FD_ISSET(i, &writeFds) && i != fd)
			send(i, bufferWrite, strlen(bufferWrite), 0);
}

int main(int argc, char **argv)
{
	if (argc != 2)									// Check if the number of command line arguments is incorrect
		ft_error("Wrong number of arguments");		// Print an error message with ft_error

	// Create the server socket
	int socketfd = socket(AF_INET, SOCK_STREAM, 0);				// Create a socket with IPv4 addressing and TCP protocol
	if (socketfd < 0)				// Check if socket creation failed			
		ft_error(NULL);								// Print an error message with ft_error
	
	// Initialise the active sockets set
	FD_ZERO(&active);				// Clear the set of active sockets
	bzero(&clients, sizeof(clients));				// place in the sizeof 'clients' zero-valued bytes in the area pointed to by '&clients'
	fdMax = socketfd;				// Variable to track the maximum socket descriptor
	FD_SET(socketfd, &active);		// Add the server socket to the set

	// Set up the server address
	struct sockaddr_in  serveraddr;				// Structure to hold the server address
	socklen_t           len;
	bzero(&serveraddr, sizeof(serveraddr));	// place in the sizeof 'serveraddr' zero-valued bytes in the area pointed to by '&serveraddr'; probably similar to struct sockaddr_in serveraddr = {0};

	serveraddr.sin_family = AF_INET;		// Set address family to IPv4
	/** check for 2130706433, as it has to stand for this machine. Instead INADDR_LOOPBACK could be an option **/
	serveraddr.sin_addr.s_addr = htonl(2130706433);		// Set the IP address to localhost   
	serveraddr.sin_port = htons(atoi(argv[1]));		// Set the port number from the command line argument

	// Bind the server socket to the specified address
	if ((bind(socketfd, (const struct sockaddr *) &serveraddr, sizeof(serveraddr))) < 0)
		ft_error(NULL);		// if binding fails: Print an error message with ft_error

	// Listen for incoming connections
	if (listen(socketfd, 10) < 0)		// 10 are 'MAX_CLIENTS', others have defined it on 128
		ft_error(NULL);		// if listening fails: Print an error message with ft_error

	while(1)
	{
		// Wait for activity on the sockets
		readFds = writeFds = active;				// Copy the active sockets 'set' for use with select()
		if (select(fdMax + 1, &readFds, &writeFds, NULL, NULL) < 0)
			continue;		// if select() fails: jumps directly to while(1), so no break, but the input is ignored. 
		
		// Check each socket for activity
		for(int fdI = 0; fdI <= fdMax; fdI++)
		{
			if (socketfd < 0)
				ft_error(NULL);
			if (FD_ISSET(fdI, &readFds) && fdI == socketfd)		// fdI == socketfd checks if the activity is on the server socket
			{
				// This is where we accept connections; new client connection
				int connfd = accept(socketfd, (struct sockaddr *)&serveraddr, &len);		// Accept a new client connection
				if (connfd < 0)
					continue;		// if accepting fails: jumps directly to for(int fdI = 0; fdI <= fdMax; fdI++), so no break, but the input is ignored.
				
				// Add the new client socket to the active set
				fdMax = connfd > fdMax ? connfd : fdMax;		// Update the maximum socket descriptor
				clients[connfd].id = idNext++;		// Store the client socket for future reference; Add the client socket to the array	
				FD_SET(connfd, &active);		// Add the client socket to the set of active sockets
				
				// Send a welcome message to the client
				sprintf(bufferWrite, "server: client %d just arrived\n", clients[connfd].id);		// Prepare the welcome message
				send_all(connfd);		// Send the welcome message to the client with send_all()
				break;
			}
			if (FD_ISSET(fdI, &readFds) && fdI != socketfd)			// if the if before does not apply: if the activity is not on the server socket
			{
				// Data received from a client
				/** check for 65536. Instead sizeof(bufferRead) - 1 could be an option **/
				int res = recv(fdI, bufferRead, 65536, 0);		// Receive data from the client
				if (res <= 0)
				{
					// Client disconnected
					sprintf(bufferWrite, "server: client %d just left\n", clients[fdI].id);		// Prepare the disconnection message
					send_all(fdI);				// Send the disconneczion message to the client with send_all()
					
					// Close the socket and remove it from the active set
					FD_CLR(fdI, &active);		// Remove the client socket from the set of active sockets
					close(fdI);		// Close the client socket
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
