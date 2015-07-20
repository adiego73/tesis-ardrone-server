#include <core/server.hpp>

DEFINE_THREAD_ROUTINE(server, data)
{
	if (data == NULL)
	{
		std::cout << "DATA cannot be NULL" << std::endl;
		exit(EXIT_FAILURE);
	}

	thread_data* param = (thread_data*) data;

//	vp_os_mutex_unlock(&param->mutex);

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

	while (message.compare("LAND") != 0)
	{
		// limpio el buffer
		bzero(buffer, BUFFER_SIZE);

		// leo lo que el cliente metio en el socket
		int request_size = read(newsockfd, buffer, BUFFER_SIZE);

		// request_size representa el total de bytes leidos
		if (request_size < 0)
		{
			std::cout << "ERROR reading socket" << errno << std::endl;
			message = "LAND";
		}
		else if (request_size == 0) // si el size del request es 0, es porque no hay un cliente conectado.
		{
			std::cout << "Client disconnected" << std::endl;
			// mando el mensaje LAND
			message = "LAND";
		}
		else
		{
			// mando cualquier otro mensaje
			message.assign(buffer, request_size);
		}

		ardrone_action action;
		int time;

		// si en el mensaje hay un |, entonces tomo la primera parte como la accion y la segunda como el tiempo en MS.
		if (message.find("|") != std::string::npos)
		{
			int pipe_pos = message.find("|");

			std::string action_msg = message.substr(0, pipe_pos);
			std::string time_msg = message.substr(pipe_pos + 1,
					message.length());

			action = get_ardrone_action(action_msg);
			// esto va a convertir el numero hasta el primer char no convertible. Si no puede convertir nada, devuelve 0
			time = strtol(time_msg.c_str(), NULL, 10);
		}
		else // si no puedo encontrar el | es porque tiene que ser LAND, TAKEOFF o HOVER.
		{
			action = get_ardrone_action(message);
			time = 0;
		}

		vp_os_mutex_lock(&param->mutex);

		param->action = action;
		param->ms_time = time;

		vp_os_mutex_unlock(&param->mutex);

		// devuelvo lo mismo que recibo. Si hay un error informo, y sigo.
		if (write(newsockfd, message.c_str(), message.length()) < 0)
		{
			std::cout << "ERROR writing the socket: " << errno << std::endl;
		}
	}

	close(newsockfd);
	close(sockfd);

	return C_OK;
}

ardrone_action get_ardrone_action(std::string action_str)
{
	if (action_str.find("RIGHT") != std::string::npos) return RIGHT;
	else if (action_str.find("LEFT") != std::string::npos) return LEFT;
	else if (action_str.find("FORWARD") != std::string::npos) return FORWARD;
	else if (action_str.find("BACKWARD") != std::string::npos) return BACKWARD;
	else if (action_str.find("UP") != std::string::npos) return UP;
	else if (action_str.find("DOWN") != std::string::npos) return DOWN;
	else if (action_str.find("LAND") != std::string::npos) return LAND;
	else if (action_str.find("TAKEOFF") != std::string::npos) return TAKEOFF;
	else return HOVER;
}

