#include <iostream>
#include <stdlib.h>
#include <boost/shared_ptr.hpp>

#include "classes/ardrone.hpp"
#include "core/server.hpp"
#include "core/video_server.hpp"
#include "core/drone.hpp"

#include "structures.hpp"

using namespace std;

int main(int argc, char** argv)
{
	bool with_video = false;
	if(argc == 2)
	{
		string option(argv[1]);
		if(option.find("--with-video") != string::npos)
		{
			with_video = true;
		}
	}

	boost::shared_ptr<thread_data> data(new thread_data());
	boost::shared_ptr<ARDrone> ardrone(new ARDrone());

	if (ardrone->open("192.168.1.1") != 1)
	{
		std::cerr << "ERROR when connecting to ARDrone" << std::endl;
		exit(EXIT_FAILURE);
	}

	cout << "Batery level: " << ardrone->getBatteryPercentage() << " %" << endl;

	ardrone->setCamera(0);
	ardrone->setFlatTrim();

	boost::thread t_server(server, data);
	boost::thread t_drone(drone_control, data, ardrone);
	if(with_video)
	{
		boost::thread t_video(video_server, data, ardrone);
	}

	t_server.join();
	t_drone.join();

	ardrone->close();
	t_server.~thread();
	t_drone.~thread();

}
