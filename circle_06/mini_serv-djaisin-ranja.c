#include <errno.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>

typedef struct s_client
{
    int id;
    char msg[999999];	// maybe reduce by one 9
}               t_client;

t_client clients[128];
int socketfd = 0, connfd = 0, fdMax = 0, idNext = 0;
fd_set readFds, writeFds, active;
struct sockaddr_in serveraddr, cli;
char bufferRead[999999], bufferWrite[999999];

void ft_error(char *string)
{
	if (string)
		write(2, string, strlen(string));
	else
    	write(2, "Fatal error\n", 12); // or 13? or strlen("Fatal error\n")
    exit(1);
}

void	send_all(int fd)
{
	for (int i = 0; i <= fdMax; i++)
	{
		if (FD_ISSET(i, &writeFds) && i != fd)
			send(i, bufferWrite, strlen(bufferWrite), 0);
	}
}

int main(int argc, char **argv)
{
	socklen_t len;
    if (argc != 2)
        ft_error("Wrong number of arguments\n");
         
	socketfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (socketfd == -1)
		ft_error(NULL);
    fdMax = socketfd;
	bzero(&serveraddr, sizeof(serveraddr)); 
	bzero(&clients, sizeof(clients));
	bzero(&bufferWrite, sizeof(bufferWrite));
	bzero(&bufferRead, sizeof(bufferRead));
	// assign IP, PORT
    int port = atoi(argv[1]);
	serveraddr.sin_family = AF_INET; 
	serveraddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	serveraddr.sin_port = htons(port); 
	// Binding newly created socket to given IP and verification 
	if ((bind(socketfd, (const struct sockaddr *)&serveraddr, sizeof(serveraddr))) != 0)
		ft_error(NULL);
	if (listen(socketfd, 128) != 0)
		ft_error(NULL);
    FD_ZERO(&active);
    FD_SET(socketfd, &active);
	
	while (1)
	{
		readFds = writeFds = active;
		if (select(fdMax + 1, &readFds, &writeFds, NULL, NULL) < 0)
			continue;
		for (int fdI = 0; fdI <= fdMax; fdI++)
		{
			if (FD_ISSET(fdI, &readFds) && fdI == socketfd)
			{
				connfd = accept(socketfd, (struct sockaddr *)&cli, &len);
				if (connfd < 0)
					continue;
				fdMax = connfd > fdMax ? connfd : fdMax;
				sprintf(bufferWrite, "server: client %d just arrived\n", idNext);
				send_all(connfd);
				bzero(&bufferWrite, strlen(bufferWrite));
				clients[connfd].id = idNext++;
				FD_SET(connfd, &active);
			}
			else if (FD_ISSET(fdI, &readFds))
			{
				int rev = recv(fdI, &bufferRead, sizeof(bufferRead), 0);
				if (rev == 0)
				{
					FD_CLR(fdI, &active);
					sprintf(bufferWrite, "server: client %d just left\n", clients[fdI].id);
					send_all(fdI);
					bzero(&bufferWrite, strlen(bufferWrite));
					bzero(&clients[fdI], sizeof(t_client));
					close(fdI);
				}
				else
				{
					for (int i = 0, j = strlen(clients[fdI].msg); bufferRead[i]; i++, j++)
					{
						clients[fdI].msg[j] = bufferRead[i];
						if (clients[fdI].msg[j] == '\n')
						{
							clients[fdI].msg[j] = '\0';
							sprintf(bufferWrite, "client %d: %s\n", clients[fdI].id, clients[fdI].msg);
							send_all(fdI);
							bzero(&bufferWrite, strlen(bufferWrite));
							bzero(&clients[fdI].msg, strlen(clients[fdI].msg));
							j = -1;
						}
					}
					bzero(&bufferRead, sizeof(bufferRead));
				}
			}
		}
	}
	return 0;
}
