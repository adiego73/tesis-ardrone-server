#include <vp_os_signal_dep.h>

/*
 * structures.hpp
 *
 *  Created on: Jul 12, 2015
 *      Author: diego
 */
#ifndef __cplusplus
#define __cplusplus
#endif

#ifndef STRUCTURES_HPP_
#define STRUCTURES_HPP_

#include <vp_os_signal.h>
#include <string>

typedef enum
{
	RIGHT, LEFT, FORWARD, BACKWARD, UP, DOWN, LAND, HOVER, TAKEOFF
} ardrone_action;

struct thread_data
{
		vp_os_mutex_t mutex;
		ardrone_action action;
		unsigned int ms_time;
};

#endif /* STRUCTURES_HPP_ */
