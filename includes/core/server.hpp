#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <string>

#ifndef PORT_NUMBER
#define PORT_NUMBER 9090
#endif

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 256
#endif

#include "structures.hpp"

extern "C"
{
// ardrone includes
#include <VP_Api/vp_api_thread_helper.h>

}

PROTO_THREAD_ROUTINE(server, data);

ardrone_action get_ardrone_action(std::string action_str);

#endif // end SERVER_HPP_
