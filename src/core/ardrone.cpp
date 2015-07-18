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
	timespec time_start, time_end;
	float time_diff = 0.0f;

	while (!exit)
	{
		vp_os_mutex_lock(&param->mutex);

		float time_left = (float) param->ms_time / 1000.0f;

		clock_gettime(CLOCK_MONOTONIC, &time_start);

		// si time_left es 0, no va a entrar aca.
		while (time_diff < time_left)
		{
			switch (param->action)
			{
				case RIGHT: // roll
					ardrone_tool_set_progressive_cmd(true, 0.01, 0, 0, 0, 0, 0);
				break;
				case LEFT: // roll
					ardrone_tool_set_progressive_cmd(true, -0.01, 0, 0, 0, 0,
							0);
				break;
				case FORWARD: // pitch
					ardrone_tool_set_progressive_cmd(true, 0, 0.01, 0, 0, 0, 0);
				break;
				case BACKWARD: // pitch
					ardrone_tool_set_progressive_cmd(true, 0, -0.01, 0, 0, 0,
							0);
				break;
				case UP: // gaz
					ardrone_tool_set_progressive_cmd(false, 0, 0, 0.01, 0, 0,
							0);
				break;
				case DOWN: // gaz
					ardrone_tool_set_progressive_cmd(false, 0, 0, -0.01, 0, 0,
							0);
				break;
				default:
				break;
			}

			clock_gettime(CLOCK_MONOTONIC, &time_end);
			time_diff = time_end.tv_sec - time_start.tv_sec;
		}

		std::cout << "action: "<<param->action << std::endl;

		if (param->action == TAKEOFF) // despegue
		{
			std::cout << "takeoff "<< std::endl;
			ardrone_tool_set_ui_pad_select(0);
			ardrone_tool_set_ui_pad_start(1);
		}
		else if (param->action == LAND) // aterrizaje
		{
			ardrone_tool_set_ui_pad_start(0);
			exit = true;
		}
		else //si no sabe que hacer, le manda hover
		{
			ardrone_tool_set_progressive_cmd(false, 0, 0, 0, 0, 0, 0);
		}

		time_diff = 0.0f;

		// pasamos a HOVER para que no se quede repitiendo siempre lo mismo en caso de que no se mande mas nada.
		//param->action = HOVER;
		//param->ms_time = 0;

		// no se puede pasar ningun parametro hasta que se desbloquee la memoria.
		vp_os_mutex_unlock(&param->mutex);
	}
	return C_OK;
}

