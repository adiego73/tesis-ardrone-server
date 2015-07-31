#ifndef STRUCTURES_HPP_
#define STRUCTURES_HPP_

#include <string>
#include <pthread.h>
#include <opencv.hpp>

#ifndef END_OK
#define END_OK 0
#endif

#ifndef END_FAIL
#define END_FAIL -1
#endif

enum ardrone_action
{
	RIGHT, LEFT, FORWARD, BACKWARD, UP, DOWN, LAND, HOVER, TAKEOFF, END
};


struct thread_data
{
		pthread_mutex_t mutex;
		ardrone_action action;
		unsigned int ms_time;
		cv::Mat frame;
};

#ifndef __DEBUG__
//#define __DEBUG__
#endif

#endif /* STRUCTURES_HPP_ */
