#include <ardrone_tool/UI/ardrone_input.h>
#include <vp_os_signal.h>
#include <vp_os_thread.h>
#include <vp_os_types.h>

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

// file include
#include "core/ardrone.hpp"
#include "structures.hpp"

DEFINE_THREAD_ROUTINE(ardrone_control, data)
{
	if (data == NULL)
	{
		std::cout << "DATA cannot be NULL" << std::endl;
		exit(EXIT_FAILURE);
	}

	thread_data* param = (thread_data*) data;

	vp_os_mutex_lock(&param->mutex);

	switch (param->action)
	{
		case RIGHT: // roll
			ardrone_tool_set_progressive_cmd(false, 0.01, 0, 0, 0, 0, 0);
		break;
		case LEFT: // roll
			ardrone_tool_set_progressive_cmd(false, -0.01, 0, 0, 0, 0, 0);
		break;
		case UP: // gaz
			ardrone_tool_set_progressive_cmd(false, 0, 0, 0.01, 0, 0, 0);
		break;
		case DOWN: // gaz
			ardrone_tool_set_progressive_cmd(false, 0, 0, -0.01, 0, 0, 0);
		break;
		case FORWARD: // pitch
			ardrone_tool_set_progressive_cmd(false, 0, 0.01, 0, 0, 0, 0);
		break;
		case BACKWARD: // pitch
			ardrone_tool_set_progressive_cmd(false, 0, -0.01, 0, 0, 0, 0);
		break;
		case LAND: // land
			ardrone_tool_set_ui_pad_start(0);
		break;
		case TAKEOFF:
			ardrone_tool_set_ui_pad_select(1);
			ardrone_tool_set_ui_pad_start(1);
		break;
		case HOVER: // hover
		default:
			ardrone_tool_set_progressive_cmd(false, 0, 0, 0, 0, 0, 0);
		break;
	}

	vp_os_mutex_unlock(&param->mutex);

	return C_OK;
}

