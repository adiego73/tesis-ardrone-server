#ifndef VIDEO_SERVER_HPP_
#define VIDEO_SERVER_HPP_

#include <boost/shared_ptr.hpp>

#include "structures.hpp"

void video_server(boost::shared_ptr<thread_data> data, boost::shared_ptr<ARDrone> ardrone);

#endif // VIDEO_SERVER_HPP_
