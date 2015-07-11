/*
 * server.cpp
 *
 *  Created on: Jul 11, 2015
 *      Author: diego
 */

#include <server.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void server_main()
{

	int PORTNUM = 9090;

	int sockfd, newsockfd;
	socklen_t clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n;

	// creo el socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0)
	{
		printf("ERROR opening socket");
		exit(EXIT_FAILURE);
	}

	// seteo la direccion del server en 0
	bzero((char *) &serv_addr, sizeof(serv_addr));

	// reasigno la direccion.
	serv_addr.sin_family = AF_INET; // internet
	serv_addr.sin_addr.s_addr = INADDR_ANY; // IP de la maquina
	serv_addr.sin_port = htons(PORTNUM); // numero de puerto

	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("ERROR on binding %d", errno);
		exit(EXIT_FAILURE);
	}

	while (true)
	{
		listen(sockfd, 1);

		clilen = sizeof(cli_addr);
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

		if (newsockfd < 0)
		{
			printf("ERROR on accept %d", errno);
			exit(EXIT_FAILURE);
		}

		bzero(buffer, 256);

		if (read(newsockfd, buffer, 255) < 0)
		{
			printf("ERROR reading from socket");
		}

		printf("Here is the message: %s\n", buffer);

		if (write(newsockfd, "I got your message", 18) < 0)
		{
			printf("ERROR writing to socket");
		}
	}
}

close (newsockfd);
close (sockfd);

}

