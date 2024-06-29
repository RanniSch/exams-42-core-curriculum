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
	char msg[1024];
}				t_client;

t_client	clients[1024];
fd_set		writeFds;
fd_set		readFds;
fd_set		active;
int 		fdMax = 0;
int			idNext = 0;
char		bufferRead[120000], bufferWrite[120000];

void	ft_error(char *string)
{
	if (string)
		write(2, string, strlen(string));
	else
		write(2, "Fatal error", strlen("Fatal error"));
	write(2, "\n", 1);
	exit(1);
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
	if (argc != 2)
		ft_error("Wrong number of arguments");

	int socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketfd < 0)
		ft_error(NULL);
	
	FD_ZERO(&active);
	bzero(&clients, sizeof(clients));
	fdMax = socketfd;
	FD_SET(socketfd, &active);

	struct sockaddr_in  serveraddr;
	socklen_t           len;
	bzero(&serveraddr, sizeof(serveraddr));

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(2130706433);
	serveraddr.sin_port = htons(atoi(argv[1]));

	if ((bind(socketfd, (const struct sockaddr *) &serveraddr, sizeof(serveraddr))) < 0)
		ft_error(NULL);

	if (listen(socketfd, 10) < 0)
		ft_error(NULL);

	while(1)
	{
		readFds = writeFds = active;
		if (select(fdMax + 1, &readFds, &writeFds, NULL, NULL) < 0)
			continue;
		for(int fdI = 0; fdI <= fdMax; fdI++)
		{
			if (socketfd < 0)
				ft_error(NULL);
			if (FD_ISSET(fdI, &readFds) && fdI == socketfd)
			{
				// This is where we accept connections.
				int connfd = accept(socketfd, (struct sockaddr *)&serveraddr, &len);
				if (connfd < 0)
					continue;
				fdMax = connfd > fdMax ? connfd : fdMax;
				clients[connfd].id = idNext++;
				FD_SET(connfd, &active);
				sprintf(bufferWrite, "server: client %d just arrived\n", clients[connfd].id);
				send_all(connfd);
				break;
			}
			if (FD_ISSET(fdI, &readFds) && fdI != socketfd)
			{
				int res = recv(fdI, bufferRead, 65536, 0);
				if (res <= 0)
				{
					sprintf(bufferWrite, "server: client %d just left\n", clients[fdI].id);
					send_all(fdI);
					FD_CLR(fdI, &active);
					close(fdI);
					break;
				}
				else
				{
					for (int i = 0, j = strlen(clients[fdI].msg); i < res; i++, j++)
					{
						clients[fdI].msg[j] = bufferRead[i];
						if (clients[fdI].msg[j] == '\n')
						{
							clients[fdI].msg[j] = '\0';
							sprintf(bufferWrite, "client %d: %s\n", clients[fdI].id, clients[fdI].msg);
							send_all(fdI);
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
