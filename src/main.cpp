#include <iostream>

extern "C"
{
	#include <ardrone_tool/ardrone_tool.h>
	#include <ardrone_tool/Navdata/ardrone_navdata_client.h>
}

#include <VP_Api/vp_api_thread_helper.h>

#include <ardrone_api.h>
#include <vp_os_signal.h>
#include <vp_os_types.h>

#include "core/server.hpp"
#include "core/ardrone.hpp"
#include "structures.hpp"

using namespace std;

std::string get_state_as_string(uint32_t state);

int main(int argc, char** argv)
{
	return ardrone_tool_main(argc, argv);
}

/*
 * Ardrone tool custom functions
 */
C_RESULT ardrone_tool_init_custom(void)
{
	thread_data * data = (thread_data *) vp_os_calloc(1, sizeof(thread_data));

	vp_os_mutex_init(&data->mutex);
	// bloqueo el mutex para que entre primero en el server
	//vp_os_mutex_lock(&data->mutex);

	ardrone_at_set_flat_trim();

	START_THREAD(server, data);
	START_THREAD(drone_control, data);

	return C_OK;
}

C_RESULT ardrone_tool_shutdown_custom(void)
{
	JOIN_THREAD(server);
	JOIN_THREAD(drone_control);

	return C_OK;
}

/*
 * Navdata functions
 */

C_RESULT navdata_init(void)
{
	return C_OK;
}

C_RESULT navdata_process(const navdata_unpacked_t* const data)
{
#ifdef __DEBUG__
	cout << "============================================" << endl;
	cout << "==============   NAVDATA INFO   ============" << endl;
	cout << "============================================" << endl;
	cout << "\t " << "Altitude: " << data->navdata_demo.altitude << endl;
	cout << "\t " << "Roll: " << data->navdata_demo.phi << endl;
	cout << "\t " << "Pitch: " << data->navdata_demo.theta << endl;
	cout << "\t " << "Yaw: " << data->navdata_demo.psi << endl;
	cout << "\t " << "State: " << data->navdata_demo.ctrl_state << endl;
#endif
	return C_OK;
}

C_RESULT navdata_release(void)
{
	return C_OK;
}

std::string get_state_as_string(uint32_t state)
{
	if (state == 131072) return "Landed";
	if (state == 393216) return "Taking-off-Floor";
	if (state == 393217) return "Taking-off-Air";
	if (state == 262144) return "Hovering";
	if (state == 524288) return "Landing";
	if (state == 458752) return "Stabilizing";
	if (state == 196608) return "Moving";
	else return "Undefined";
}

/*
 * Tables
 */

BEGIN_THREAD_TABLE
	THREAD_TABLE_ENTRY(server, 20)
	THREAD_TABLE_ENTRY(drone_control, 20)
	THREAD_TABLE_ENTRY(navdata_update, 20 )
END_THREAD_TABLE

BEGIN_NAVDATA_HANDLER_TABLE
	NAVDATA_HANDLER_TABLE_ENTRY(navdata_init, navdata_process, navdata_release, NULL)
END_NAVDATA_HANDLER_TABLE
