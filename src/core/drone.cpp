#include "core/drone.hpp"

void* drone_control(void* data)
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

	ARDrone ardrone;

	if (!ardrone.open("192.168.1.1"))
	{
		std::cout << "ERROR when connecting to ARDrone" << std::endl;
	}

	while (!exit)
	{
		pthread_mutex_lock(&param->mutex);

		float time_left_sec = (float) param->ms_time / 1000.0f;
		time_diff_sec = 0.0f;

		clock_gettime(CLOCK_MONOTONIC, &time_start);

		// si time_left es 0, no va a entrar aca.
		while (time_diff_sec < time_left_sec)
		{
			switch (param->action)
			{
				case RIGHT: // roll
					ardrone.move3D(0, 0, 0, -0.05);
				break;
				case LEFT: // roll
					ardrone.move3D(0, 0, 0, 0.05);
				break;
				case FORWARD: // pitch
					ardrone.move3D(0.05, 0, 0, 0);
				break;
				case BACKWARD: // pitch
					ardrone.move3D(-0.05, 0, 0, 0);
				break;
				case UP: // gaz
					ardrone.move3D(0, 0, 0.1, 0);
				break;
				case DOWN: // gaz
					ardrone.move3D(0, 0, -0.1, 0);
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
			ardrone.takeoff();
		}
		else if (param->action == LAND) // aterrizaje
		{
			ardrone.landing();
		}
		else if (param->action == END)
		{
			// aterrizo el robot y salgo.
			ardrone.landing();
			exit = true;
		}
		else // HOVER al final de todo, excepto caundo es TAKEOFF o LAND
		{
			ardrone.move3D(0, 0, 0, 0);
			// al final siempre entra aca. Si no le pongo esto, el robot se queda con lo ultimo que le mande.
			param->action = HOVER;
			param->ms_time = 0;
		}

		// obtengo el frame del robot.
		cv::Mat img = ardrone.getImage();
		param->frame = img;

		// no se puede pasar ningun parametro hasta que se desbloquee la memoria.
		pthread_mutex_unlock(&param->mutex);
	}

	std::cout << "\tTURNING OFF ARDRONE CONTROL" << std::endl;

	return END_OK;
}