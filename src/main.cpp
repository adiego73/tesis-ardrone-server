#include <classes/ardrone.hpp>
#include <iostream>

#include "core/server.hpp"
#include "structures.hpp"

using namespace std;

int main(int argc, char** argv)
{
	thread_data* data = (thread_data*)malloc(sizeof(thread_data));

	pthread_t threads[3];

	pthread_mutex_init(&data->mutex, NULL);

	pthread_create(&threads[0], NULL, server, &data);
	pthread_create(&threads[1], NULL, drone_control, &data);
	pthread_create(&threads[2], NULL, video_server, &data);

}
