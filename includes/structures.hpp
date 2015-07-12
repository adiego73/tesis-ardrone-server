/*
 * structures.hpp
 *
 *  Created on: Jul 12, 2015
 *      Author: diego
 */

#ifndef STRUCTURES_HPP_
#define STRUCTURES_HPP_

#include <vp_os_signal.h>
#include <string>

struct thread_data
{
		vp_os_mutex_t mutex;
		std::string action;
		int ms_time;
};

#endif /* STRUCTURES_HPP_ */
