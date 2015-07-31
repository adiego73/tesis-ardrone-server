#ifndef DRONE_HPP_
#define DRONE_HPP_

#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "classes/ardrone.hpp"
#include "structures.hpp"


#ifndef PORT_NUMBER
#define PORT_NUMBER 9090
#endif

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 256
#endif

void* drone_control(void* data);

#endif // end DRONE_HPP_
