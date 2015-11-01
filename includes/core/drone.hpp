#ifndef DRONE_HPP_
#define DRONE_HPP_

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <boost/shared_ptr.hpp>
#include <ardrone.h>

#include "structures.hpp"


#ifndef PORT_NUMBER
#define PORT_NUMBER 9090
#endif

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 256
#endif

void drone_control(boost::shared_ptr<thread_data> data, boost::shared_ptr<ARDrone> ardrone);

#endif // end DRONE_HPP_
