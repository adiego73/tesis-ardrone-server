/*
 * ardrone.hpp
 *
 *  Created on: Jul 12, 2015
 *      Author: diego
 */

#ifndef ARDRONE_HPP_
#define ARDRONE_HPP_

extern "C"
{
// ardrone includes
#include <ardrone_tool/UI/ardrone_input.h>
#include <vp_os_thread.h>
#include <VP_Api/vp_api_thread_helper.h>
#include <vp_os_signal.h>

}

PROTO_THREAD_ROUTINE(ardrone_control, data);


#endif /* ARDRONE_HPP_ */
