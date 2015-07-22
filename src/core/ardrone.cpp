#include "core/ardrone.hpp"

DEFINE_THREAD_ROUTINE(drone_control, data)
{
	if (data == NULL)
	{
		std::cout << "DATA cannot be NULL" << std::endl;
		exit(EXIT_FAILURE);
	}

	thread_data* param = (thread_data*) data;

	bool exit = false;
	timespec time_start, time_now;
	float time_diff_sec = 0.0f;

	while (!exit)
	{
		vp_os_mutex_lock(&param->mutex);

		float time_left_sec = (float) param->ms_time / 1000.0f;
		time_diff_sec = 0.0f;

		clock_gettime(CLOCK_MONOTONIC, &time_start);

		// si time_left es 0, no va a entrar aca.
		while (time_diff_sec < time_left_sec)
		{
			switch (param->action)
			{
				case RIGHT: // roll
					ardrone_tool_set_progressive_cmd(true, 0.05, 0, 0, 0, 0, 0);
				break;
				case LEFT: // roll
					ardrone_tool_set_progressive_cmd(true, -0.05, 0, 0, 0, 0, 0);
				break;
				case FORWARD: // pitch
					ardrone_tool_set_progressive_cmd(true, 0, -0.05, 0, 0, 0, 0);
				break;
				case BACKWARD: // pitch
					ardrone_tool_set_progressive_cmd(true, 0, 0.05, 0, 0, 0, 0);
				break;
				case UP: // gaz
					ardrone_tool_set_progressive_cmd(false, 0, 0, 0.1, 0, 0, 0);
				break;
				case DOWN: // gaz
					ardrone_tool_set_progressive_cmd(false, 0, 0, -0.1, 0, 0,
							0);
				break;
				default:
					param->ms_time = 0;
					// do nothing
				break;
			}

			clock_gettime(CLOCK_MONOTONIC, &time_now);
			time_diff_sec = time_now.tv_sec - time_start.tv_sec;
		}

		if (param->action == TAKEOFF) // despegue
		{
			ardrone_tool_set_ui_pad_start(1);
		}
		else if (param->action == LAND) // aterrizaje
		{
			ardrone_tool_set_ui_pad_start(0);
		}
		else if (param->action == EXIT)
		{
			// aterrizo el robot y salgo.
			ardrone_tool_set_ui_pad_start(0);
			exit = true;
		}
		else // HOVER al final de todo, excepto caundo es TAKEOFF o LAND
		{
			ardrone_tool_set_progressive_cmd(false, 0, 0, 0, 0, 0, 0);

			// al final siempre entra aca. Si no le pongo esto, el robot se queda con lo ultimo que le mande.
			param->action = HOVER;
			param->ms_time = 0;
		}

		// no se puede pasar ningun parametro hasta que se desbloquee la memoria.
		vp_os_mutex_unlock(&param->mutex);
	}

	std::cout << "\tTURNING OFF ARDRONE CONTROL" << std::endl;

	return C_OK;
}

