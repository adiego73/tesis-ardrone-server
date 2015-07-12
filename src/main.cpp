#include <iostream>

extern "C" {
	#include <ardrone_tool/ardrone_tool.h>
}

#include <VP_Api/vp_api_thread_helper.h>
#include <ardrone_api.h>
#include <vp_os_signal.h>
#include <vp_os_types.h>

#include "core/server.hpp"
#include "core/ardrone.hpp"
#include "structures.hpp"

using namespace std;

int main(int argc, char** argv)
{
	return ardrone_tool_main(argc, argv);
}

C_RESULT ardrone_tool_init_custom(void)
{
	thread_data data;
	vp_os_mutex_init(&data.mutex);

	ardrone_at_set_flat_trim();

	START_THREAD(server, &data);
	START_THREAD(ardrone_control, &data);

	return C_OK;
}

C_RESULT ardrone_tool_shutdown_custom(void)
{
	JOIN_THREAD(server);
	JOIN_THREAD(ardrone_control);

	return C_OK;
}

BEGIN_THREAD_TABLE
	THREAD_TABLE_ENTRY(server, 20)
	THREAD_TABLE_ENTRY(ardrone_control, 20)
END_THREAD_TABLE
