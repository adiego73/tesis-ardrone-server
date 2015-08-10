#include "core/drone.hpp"

void drone_control(boost::shared_ptr<thread_data> param,
		boost::shared_ptr<ARDrone> ardrone)
{
	if (param == NULL)
	{
		std::cerr << "ERROR THREAD DATA cannot be NULL" << std::endl;
		exit(EXIT_FAILURE);
	}

	bool finish = false;
	timespec time_start, time_now;
	float time_diff_sec = 0.0f;

	while (!finish)
	{
		// mutex lock
		param->m_mutex.lock_shared();

		float time_left_sec = (float) param->ms_time / 1000.0f;
		time_diff_sec = 0.0f;

		clock_gettime(CLOCK_MONOTONIC, &time_start);

		// si time_left es 0, no va a entrar aca.
		while (time_diff_sec < time_left_sec)
		{
			switch (param->action)
			{
				case RIGHT: // roll
					ardrone->move3D(0, -0.5, 0, 0);
				break;
				case LEFT: // roll
					ardrone->move3D(0, 0.5, 0, 0);
				break;
				case FORWARD: // pitch
					ardrone->move3D(0.5, 0, 0, 0);
				break;
				case BACKWARD: // pitch
					ardrone->move3D(-0.5, 0, 0, 0);
				break;
				case UP: // gaz
					ardrone->move3D(0, 0, 1, 0);
				break;
				case DOWN: // gaz
					ardrone->move3D(0, 0, 1, 0);
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
			ardrone->takeoff();
		}
		else if (param->action == LAND) // aterrizaje
		{
			ardrone->landing();
		}
		else if (param->action == END)
		{
			// aterrizo el robot y salgo.
			ardrone->landing();
			finish = param->finish;
		}
		else // HOVER al final de todo, excepto caundo es TAKEOFF o LAND
		{
			ardrone->move3D(0, 0, 0, 0);
		}

		// al final siempre entra aca. Si no le pongo esto, el robot se queda con lo ultimo que le mande.
		param->action = HOVER;
		param->ms_time = 0;

		// no se puede pasar ningun parametro hasta que se desbloquee la memoria.
		param->m_mutex.unlock_shared();
	}

	std::cout << "\tTURNING OFF ARDRONE CONTROL" << std::endl;
}
