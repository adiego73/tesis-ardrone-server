#ifndef VIDEO_SERVER_HPP_
#define VIDEO_SERVER_HPP_

#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <boost/shared_ptr.hpp>

#include "structures.hpp"

#ifndef VIDEO_PORT_NUMBER
#define VIDEO_PORT_NUMBER 9091
#endif

void video_server(boost::shared_ptr<thread_data> data, boost::shared_ptr<ARDrone> ardrone);

#endif // VIDEO_SERVER_HPP_
