#ifndef STRUCTURES_HPP_
#define STRUCTURES_HPP_

#include <string>
#include <opencv.hpp>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>

#include "classes/ardrone.hpp"

#ifndef END_OK
#define END_OK 0
#endif

#ifndef END_FAIL
#define END_FAIL -1
#endif

#ifndef MAX_THREADS
#define MAX_THREADS 3
#endif

enum ardrone_action
{
	RIGHT, LEFT, FORWARD, BACKWARD, UP, DOWN, LAND, HOVER, TAKEOFF, END
};


typedef struct
{
		boost::mutex m_mutex;
		ardrone_action action;
		unsigned int ms_time;
}thread_data;

#ifndef __DEBUG__
//#define __DEBUG__
#endif

#endif /* STRUCTURES_HPP_ */
