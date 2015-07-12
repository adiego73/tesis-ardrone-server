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
#include <VP_Api/vp_api_thread_helper.h>

}

PROTO_THREAD_ROUTINE(ardrone_control, data);


#endif /* ARDRONE_HPP_ */
