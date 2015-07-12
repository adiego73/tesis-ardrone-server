/*
 * ardrone.cpp
 *
 *  Created on: Jul 11, 2015
 *      Author: diego
 */

// ardrone includes
#include <vp_os_thread.h>

// file include
#include "core/ardrone.hpp"

DEFINE_THREAD_ROUTINE(ardrone_control, data)
{
	return C_OK;
}


