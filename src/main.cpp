#include <iostream>

extern "C"
{
	#include <ardrone_tool/ardrone_tool.h>
	#include <ardrone_tool/ardrone_tool_configuration.h>
	#include <ardrone_tool/Navdata/ardrone_navdata_client.h>
}

	#include <ardrone_tool/Video/video_stage.h>
#include <VP_Api/vp_api_thread_helper.h>

#include <ardrone_api.h>
#include <vp_os_signal.h>
#include <vp_os_types.h>

#include "core/server.hpp"
#include "core/ardrone.hpp"
#include "core/video.hpp"
#include "structures.hpp"

using namespace std;

std::string get_state_as_string(uint32_t state);

int main(int argc, char** argv)
{
	// TODO add video streaming
	return ardrone_tool_main(argc, argv);
}

/*
 * Ardrone tool custom functions
 */
C_RESULT ardrone_tool_init_custom(void)
{

	thread_data * data = (thread_data *) vp_os_calloc(1, sizeof(thread_data));

	vp_os_mutex_init(&data->mutex);

	ardrone_at_set_flat_trim();

	START_THREAD(server, data);
	START_THREAD(drone_control, data);

	specific_parameters_t* cfg = (specific_parameters_t *) vp_os_calloc(1, sizeof(specific_parameters_t));

	specific_stages_t *pre_stages = (specific_stages_t *)vp_os_calloc (1, sizeof (specific_stages_t));
	specific_stages_t *post_stages = (specific_stages_t *)vp_os_calloc (1, sizeof (specific_stages_t));
	vp_api_picture_t *in_picture = (vp_api_picture_t *)vp_os_calloc (1, sizeof (vp_api_picture_t));
	vp_api_picture_t *out_picture = (vp_api_picture_t *)vp_os_calloc (1, sizeof (vp_api_picture_t));

	out_picture->format = PIX_FMT_RGB24;

	in_picture->width = VGA_WIDTH;
	in_picture->height = VGA_HEIGHT;

	out_picture->framerate = 24;

	out_picture->width = in_picture->width;
	out_picture->height	= in_picture->height;

	out_picture->y_buf = (uint8_t *) vp_os_malloc( out_picture->width * out_picture->height * 3 ); // RGB24 needs 3 bytes per pixel
	out_picture->cr_buf	= NULL;
	out_picture->cb_buf	= NULL;

	out_picture->y_line_size = out_picture->width * 3; // RGB24 needs 3 bytes per pixel
	out_picture->cb_line_size = 0;
	out_picture->cr_line_size = 0;

	// no hay pre-stages
	pre_stages->length = 0;
	pre_stages->stages_list = NULL;

	// solo hay 1 post-stage
	post_stages->length = 1;
	post_stages->stages_list = (vp_api_io_stage_t*) vp_os_calloc(post_stages->length, sizeof(vp_api_io_stage_t));

	post_stages->stages_list[0].type = VP_API_OUTPUT_SDL; // Debug info
	post_stages->stages_list[0].cfg  = NULL;
	post_stages->stages_list[0].funcs  = video_process_functions;

	START_THREAD(video_stage, cfg);
	video_stage_init();
	video_stage_resume_thread();

	return C_OK;
}

C_RESULT ardrone_tool_shutdown_custom(void)
{
	JOIN_THREAD(server);
	JOIN_THREAD(drone_control);

	video_stage_resume_thread();
	JOIN_THREAD(video_stage);

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
	THREAD_TABLE_ENTRY(video_stage, 20)
END_THREAD_TABLE

BEGIN_NAVDATA_HANDLER_TABLE
	NAVDATA_HANDLER_TABLE_ENTRY(navdata_init, navdata_process, navdata_release, NULL)
END_NAVDATA_HANDLER_TABLE
