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
#include <string>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

void server_main()
{
	cout << endl << "SERVER MAIN START.." << endl;
	int sockfd, newsockfd;
	socklen_t clilen;
	char buffer[BUFFER_SIZE];
	struct sockaddr_in serv_addr, cli_addr;

	// creo el socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0)
	{
		cout << "ERROR opening socket";
		exit(EXIT_FAILURE);
	}

	// seteo la direccion del server en 0
	bzero((char *) &serv_addr, sizeof(serv_addr));

	// reasigno la direccion.
	serv_addr.sin_family = AF_INET; // internet
	serv_addr.sin_addr.s_addr = INADDR_ANY; // IP de la maquina
	serv_addr.sin_port = htons(PORT_NUMBER); // numero de puerto

	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("ERROR on binding %d", errno);
		exit(EXIT_FAILURE);
	}

	// espero una conexion. El limite de espera es una conexion
	listen(sockfd, 1);

	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

	if (newsockfd < 0)
	{
		printf("ERROR on accept %d", errno);
		exit(EXIT_FAILURE);
	}

	string message(buffer, BUFFER_SIZE);

	while (message.compare("exit") != 0)
	{
		cout << "while" << endl;

		// limpio el buffer
		bzero(buffer, BUFFER_SIZE);

		// leo lo que el cliente metio en el socket
		if (read(newsockfd, buffer, BUFFER_SIZE) < 0)
		{
			cout << "ERROR reading socket";
			break;
		}

		message.assign(buffer);

		cout << message << endl;

		// si en el mensaje hay un |, entonces tomo la primera parte como la accion y la segunda como el tiempo en MS.
		if (message.find("|") != string::npos)
		{
			string action = message.substr(0, message.find("|"));
			string time = message.substr(message.find("|"), message.length());

			cout << "action: " << action << " time: " << time << endl;
		}
		// si no puedo encontrar el | es porque tiene que ser LAND o HOVER.
		else
		{
			// el mensaje es LAND
			if (message.compare("LAND") == 0)
			{
				cout << "land" << endl;
			}
			//  cualquier otra cosa la tomo como HOVER
			else
			{
				cout << "hover" << endl;
			}
		}

		// devuelvo lo mismo que recibo.
		if (write(newsockfd, buffer, BUFFER_SIZE) < 0)
		{
			cout << "ERROR writing the socket";
			break;
		}
	}

	close(newsockfd);
	close(sockfd);

}

