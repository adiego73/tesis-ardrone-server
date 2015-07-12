//============================================================================
// Name        : tesis-ardrone-server.cpp
// Author      :
// Version     :
// Copyright   :
// Description : Hello World in C++, Ansi-style
//============================================================================

// system includes
#include <iostream>

// ardrone includes
#include <ardrone_tool/ardrone_tool.h>
#include <VP_Api/vp_api_thread_helper.h>

// proj includes
#include "structures.hpp"

using namespace std;

int main(int argc, char** argv)
{
	return ardrone_tool_main(argc, argv);
}

C_RESULT ardrone_tool_init_custom(void)
{
	START_THREAD(server, NULL);
	START_THREAD(ardrone_control, NULL);

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
