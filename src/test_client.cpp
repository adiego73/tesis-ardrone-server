#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string>
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
	extern struct hostent *server;

	char buffer[BUFFER_SIZE];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0)
	{
		std::cout << "ERROR on creating socket. Error No: " << errno
				<< std::endl;
		exit(EXIT_FAILURE);
	}

	server = gethostbyname(HOST_NAME);

	if (server == NULL)
	{
		std::cout << "ERROR there is no host called '" << HOST_NAME
				<< "'. Error No: " << errno << std::endl;
		exit(EXIT_FAILURE);
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	inet_aton(server->h_addr_list[0], &serv_addr.sin_addr);
	serv_addr.sin_port = htons(PORT_NUMBER);

	if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{
		std::cout << "ERROR connecting to socket. Error No: " << errno
				<< std::endl;
		exit(EXIT_FAILURE);
	}

	std::string message = "";

	do
	{
		std::cout << "MESSAGE: ";
		std::cin >> buffer;

		message.assign(buffer);

		if (write(sockfd, buffer, BUFFER_SIZE))
		{
			std::cout << "ERROR writing to socket. Error No: " << errno
					<< std::endl;
			break;
		}

		bzero(buffer, BUFFER_SIZE);

		if (read(sockfd, buffer, BUFFER_SIZE) < 0)
		{
			std::cout << "ERROR reading from socket. Error No: " << errno
					<< std::endl;
			break;
		}

		std::cout << "SERVER RESPONSE: " << buffer << std::endl;

	} while (message.compare("TAKEOFF") != 0);

	close(sockfd);
	return 0;
}

