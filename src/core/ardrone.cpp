/*
 * ardrone.cpp
 *
 *  Created on: Jul 11, 2015
 *      Author: diego
 */
#ifndef __cplusplus
#define __cplusplus
#endif

//system includes
#include <iostream>
#include <stdlib.h>

// ardrone includes
#include <vp_os_thread.h>

// file include
#include "core/ardrone.hpp"
#include "structures.hpp"

DEFINE_THREAD_ROUTINE(ardrone_control, data)
{
	if(data == NULL)
	{
		std::cout << "DATA cannot be NULL" << std::endl;
		exit(EXIT_FAILURE);
	}

	thread_data* param = (thread_data*) data;

	return C_OK;
}


