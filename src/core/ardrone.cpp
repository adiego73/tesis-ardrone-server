#include "core/ardrone.hpp"

DEFINE_THREAD_ROUTINE(ardrone_control, data)
{
	if (data == NULL)
	{
		std::cout << "DATA cannot be NULL" << std::endl;
		exit(EXIT_FAILURE);
	}

	thread_data* param = (thread_data*) data;
	timespec time_start, time_end;
	float time_diff = 0.0f;

	vp_os_mutex_lock(&param->mutex);

	float time_left = (float)param->ms_time / 1000.0f;

	clock_gettime(CLOCK_MONOTONIC, &time_start);

	while (time_diff < time_left)
	{
		switch (param->action)
		{
			case RIGHT: // roll
				ardrone_tool_set_progressive_cmd(false, 0.01, 0, 0, 0, 0, 0);
			break;
			case LEFT: // roll
				ardrone_tool_set_progressive_cmd(false, -0.01, 0, 0, 0, 0, 0);
			break;
			case FORWARD: // pitch
				ardrone_tool_set_progressive_cmd(false, 0, 0.01, 0, 0, 0, 0);
			break;
			case BACKWARD: // pitch
				ardrone_tool_set_progressive_cmd(false, 0, -0.01, 0, 0, 0, 0);
			break;
			case UP: // gaz
				ardrone_tool_set_progressive_cmd(false, 0, 0, 0.01, 0, 0, 0);
			break;
			case DOWN: // gaz
				ardrone_tool_set_progressive_cmd(false, 0, 0, -0.01, 0, 0, 0);
			break;
			case LAND: // land
				ardrone_tool_set_ui_pad_start(0);
				time_left = 0;
			break;
			case TAKEOFF:
				ardrone_tool_set_ui_pad_select(1);
				ardrone_tool_set_ui_pad_start(1);
				time_left = 0;
			break;
			case HOVER: // hover
			default:
				ardrone_tool_set_progressive_cmd(false, 0, 0, 0, 0, 0, 0);
				time_left = 0;
			break;
		}

		clock_gettime(CLOCK_MONOTONIC, &time_end);
		time_diff = time_end.tv_sec - time_start.tv_sec;
	}

	vp_os_mutex_unlock(&param->mutex);

	return C_OK;
}

