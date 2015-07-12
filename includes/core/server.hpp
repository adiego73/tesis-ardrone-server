#ifndef SERVER_HPP_
#define SERVER_HPP_

#ifndef PORT_NUMBER
#define PORT_NUMBER 9090
#endif

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 256
#endif

extern "C"
{
// ardrone includes
#include <VP_Api/vp_api_thread_helper.h>

}

PROTO_THREAD_ROUTINE(server, data);

#endif // end SERVER_HPP_
