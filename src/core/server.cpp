/*
 * server.cpp
 *
 *  Created on: Jul 11, 2015
 *      Author: diego
 */

#ifndef __cplusplus
#define __cplusplus
#endif

// file include
#include <core/server.hpp>
#include "structures.hpp"

// system includes
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <strings.h>
#include <unistd.h>

// system net includes
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

DEFINE_THREAD_ROUTINE(server, data)
{
	if (data == NULL)
	{
		std::cout << "DATA cannot be NULL" << std::endl;
		exit(EXIT_FAILURE);
	}

	thread_data* param = (thread_data*) data;

	std::cout << std::endl << "SERVER MAIN START.." << std::endl;
	int sockfd, newsockfd;
	socklen_t clilen;
	char buffer[BUFFER_SIZE];
	struct sockaddr_in serv_addr, cli_addr;

	// creo el socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0)
	{
		std::cout << "ERROR opening socket";
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
		std::cout << "ERROR on binding " << errno << std::endl;
		exit(EXIT_FAILURE);
	}

	// espero una conexion. El limite de espera es una conexion
	listen(sockfd, 1);

	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

	if (newsockfd < 0)
	{
		std::cout << "ERROR on accept " << errno << std::endl;
		exit(EXIT_FAILURE);
	}

	std::string message(buffer, BUFFER_SIZE);

	while (message.compare("exit") != 0)
	{
		// limpio el buffer
		bzero(buffer, BUFFER_SIZE);

		// leo lo que el cliente metio en el socket
		if (read(newsockfd, buffer, BUFFER_SIZE) < 0)
		{
			std::cout << "ERROR reading socket" << errno << std::endl;
			break;
		}

		message.assign(buffer);

		std::cout << "DEBUG: " << message << std::endl;

		std::string action;
		std::string time;

		// si en el mensaje hay un |, entonces tomo la primera parte como la accion y la segunda como el tiempo en MS.
		if (message.find("|") != std::string::npos)
		{
			action = message.substr(0, message.find("|"));
			time = message.substr(message.find("|"), message.length());
		}
		// si no puedo encontrar el | es porque tiene que ser LAND o HOVER.
		else
		{
			// el mensaje es LAND
			if (message.compare("LAND") == 0)
			{
				action = "LAND";
				time = "0";
			}
			//  cualquier otra cosa la tomo como HOVER
			else
			{
				action = "HOVER";
				time = "0";
			}
		}

		std::cout << "DEBUG: " << "action -> " << action << " time -> " << time << std::endl;

		vp_os_mutex_lock(&param->mutex);

		param->action = action;
		param->ms_time = atoi(time.c_str());;

		vp_os_mutex_unlock(&param->mutex);

		// devuelvo lo mismo que recibo.
		if (write(newsockfd, buffer, BUFFER_SIZE) < 0)
		{
			std::cout << "ERROR writing the socket: " << errno << std::endl;
			break;
		}
	}

	close(newsockfd);
	close(sockfd);

	return C_OK;
}

