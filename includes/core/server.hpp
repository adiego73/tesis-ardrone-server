#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <strings.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <vp_os_signal.h>
#include <vp_os_thread.h>
#include <vp_os_types.h>

#include <VP_Api/vp_api_thread_helper.h>

#include "structures.hpp"


#ifndef PORT_NUMBER
#define PORT_NUMBER 9090
#endif

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 256
#endif

PROTO_THREAD_ROUTINE(server, data);

ardrone_action get_ardrone_action(std::string action_str);

#endif // end SERVER_HPP_
