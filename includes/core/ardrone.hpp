#ifndef ARDRONE_HPP_
#define ARDRONE_HPP_

#include <iostream>
#include <stdlib.h>
#include <time.h>

extern "C"
{
	#include <ardrone_tool/UI/ardrone_input.h>
}

#include <vp_os_signal.h>
#include <vp_os_thread.h>

#include <VP_Api/vp_api_thread_helper.h>

#include "structures.hpp"

PROTO_THREAD_ROUTINE(drone_control, data);

#endif /* ARDRONE_HPP_ */
