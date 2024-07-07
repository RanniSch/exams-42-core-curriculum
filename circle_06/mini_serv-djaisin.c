#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

typedef struct s_client
{
    int id;
    char msg[696968];
}   t_client;

t_client clients[128];
int sockfd = 0, connfd = 0, maxFd = 0, idNext = 0;
fd_set readfds, writefds, activefds;
struct sockaddr_in servaddr, cli;
char readbuff[696968], writebuff[696968];

void error(char *msg)
{
	if (msg)
		write(2, msg, strlen(msg));
	else
    	write(2, "Fatal error\n", 13);
    exit(1);
}

void	sendAll(int connfd)
{
	for (int fdId = 0; fdId <= maxFd; fdId++)
	{
		if (FD_ISSET(fdId, &writefds) && fdId != connfd)
			send(fdId, writebuff, strlen(writebuff), 0);
	}
}

int main(int argc, char **argv)
{
	socklen_t len;
    if (argc != 2)
        error("Wrong number of arguments\n");
	// socket create and verification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1)
		error(NULL);
    maxFd = sockfd;
	bzero(&servaddr, sizeof(servaddr)); 
	bzero(&clients, sizeof(clients));
	bzero(&writebuff, sizeof(writebuff));
	bzero(&readbuff, sizeof(readbuff));
	// assign IP, PORT
    int port = atoi(argv[1]);
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(port); 
	// Binding newly created socket to given IP and verification 
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
		error(NULL);
	if (listen(sockfd, 128) != 0)
		error(NULL);
    FD_ZERO(&activefds);
    FD_SET(sockfd, &activefds);
	
	while (6969)
	{
		readfds = writefds = activefds;
		if (select(maxFd + 1, &readfds, &writefds, NULL, NULL) < 0)
			continue;
		for (int fdId = 0; fdId <= maxFd; fdId++)
		{
			if (FD_ISSET(fdId, &readfds) && fdId == sockfd)
			{
				connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
				if (connfd < 0)
					continue;
				maxFd = connfd > maxFd ? connfd : maxFd;
				sprintf(writebuff, "server: client %d just arrived\n", idNext);
				sendAll(connfd);
				bzero(&writebuff, strlen(writebuff));
				clients[connfd].id = idNext++;
				FD_SET(connfd, &activefds);
			}
			else if (FD_ISSET(fdId, &readfds))
			{
				int readCount = recv(fdId, &readbuff, sizeof(readbuff), 0);
				if (readCount == 0)
				{
					FD_CLR(fdId, &activefds);
					sprintf(writebuff, "server: client %d just left\n", clients[fdId].id);
					sendAll(fdId);
					bzero(&writebuff, strlen(writebuff));
					bzero(&clients[fdId], sizeof(t_client));
					close(fdId);
				}
				else
				{
					for (int i = 0, j = strlen(clients[fdId].msg); readbuff[i]; i++, j++)
					{
						clients[fdId].msg[j] = readbuff[i];
						if (readbuff[i] == '\n')
						{
							clients[fdId].msg[j] = '\0';
							sprintf(writebuff, "client %d: %s\n", clients[fdId].id, clients[fdId].msg);
							sendAll(fdId);
							bzero(writebuff, strlen(writebuff));
							bzero(&clients[fdId].msg, strlen(clients[fdId].msg));
							j = -1;
						}
					}
					bzero(readbuff, sizeof(readbuff));
				}
			}
		}
	}
}
