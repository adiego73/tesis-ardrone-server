#include <iostream>
#include <stdlib.h>

#include "classes/ardrone.hpp"
#include "core/server.hpp"
#include "core/video_server.hpp"
#include "core/drone.hpp"

#include "structures.hpp"

using namespace std;

int main(int argc, char** argv)
{
	thread_data* data = (thread_data*) malloc(sizeof(thread_data));

	boost::thread t_server(server, data);
	boost::thread t_drone(drone_control, data);
	boost::thread t_video(video_server, data);

	t_server.join();
	t_drone.join();
	t_video.join();

}
