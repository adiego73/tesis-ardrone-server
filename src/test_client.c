#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 256
#endif

#ifndef PORT_NUMBER
#define PORT_NUMBER 9090
#endif

#ifndef HOST_NAME
#define HOST_NAME "localhost"
#endif

int main(int argc, char *argv[])
{
	int sockfd;
	struct sockaddr_in serv_addr;
	struct hostent *server;

	char buffer[BUFFER_SIZE];
	char reponse_buffer[BUFFER_SIZE];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0)
	{
		printf("ERROR on creating socket. Error No: %d \n", errno);
		exit(EXIT_FAILURE);
	}

	server = gethostbyname(HOST_NAME);

	if (server == NULL)
	{
		printf("ERROR there is no host called '%s'. Error No: %d \n", HOST_NAME,
				errno);
		exit(EXIT_FAILURE);
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	inet_aton(server->h_addr_list[0], &serv_addr.sin_addr);
	serv_addr.sin_port = htons(PORT_NUMBER);

	if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("ERROR connecting to socket. Error No: %d \n", errno);
		exit(EXIT_FAILURE);
	}

	while (strcmp(buffer, "EXIT") != 0)
	{
		bzero(buffer, BUFFER_SIZE);

		printf("MESSAGE: ");
		fgets(buffer, BUFFER_SIZE, stdin);

		if (write(sockfd, buffer, BUFFER_SIZE) < 0)
		{
			printf("ERROR writing to socket. Error No: %d \n", errno);
			break;
		}

		bzero(reponse_buffer, BUFFER_SIZE);

		if (read(sockfd, reponse_buffer, BUFFER_SIZE) < 0)
		{
			printf("ERROR reading from socket. Error No: %d \n", errno);
			break;
		}

		printf("%s", reponse_buffer);
	}

	printf("\tEXIT CLIENT");

	close(sockfd);
	return 0;
}

