cmake_minimum_required(VERSION 2.8.4)

message(STATUS "Project path is " ${PROJECT_SOURCE_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/)

set(SOURCES ${PROJECT_SOURCE_DIR}/src/core/drone.cpp 
			${PROJECT_SOURCE_DIR}/src/core/server.cpp 
			${PROJECT_SOURCE_DIR}/src/core/video_server.cpp)

set(HEADERS ${PROJECT_SOURCE_DIR}/includes/structures.hpp 
			${PROJECT_SOURCE_DIR}/includes/core/drone.hpp 
			${PROJECT_SOURCE_DIR}/includes/core/server.hpp 
			${PROJECT_SOURCE_DIR}/includes/core/video_server.hpp)

add_executable(server main.cpp ${SOURCES} ${HEADERS})
#add_executable(client test_client.c)

include_directories(../includes ../includes/core /opt/boost_1_57_0/include /opt/cvdrone/include  /usr/local/include/opencv /usr/local/include/opencv2)

# pthread
find_library(PTHREAD_LIB NAMES pthread PATHS "/usr/local/lib")

# opencv
find_library(OPENCV_CORE_LIB NAMES opencv_core PATHS "/usr/local/lib")
find_library(OPENCV_HIGHGUI_LIB NAMES opencv_highgui PATHS "/usr/local/lib")
find_library(OPENCV_IMGPROC_LIB NAMES opencv_imgproc PATHS "/usr/local/lib")
find_library(OPENCV_VIDEO_LIB NAMES opencv_video PATHS "/usr/local/lib")

# boost
find_library(BOOST_THREAD_LIB NAMES boost_thread PATHS "/opt/boost_1_57_0/lib")
find_library(BOOST_SYSTEM_LIB NAMES boost_system PATHS "/opt/boost_1_57_0/lib")

# cvdrone
find_library(CVDRONE_LIB NAMES cvdrone PATHS "/opt/cvdrone/lib")

# fmpeg libs
find_library(AVDEVICE_LIB NAMES avdevice PATHS "/usr/local/lib")
find_library(AVFILTER_LIB NAMES avfilter PATHS "/usr/local/lib")
find_library(SWSCALE_LIB NAMES swscale PATHS "/usr/local/lib")
find_library(AVFORMAT_LIB NAMES avformat PATHS "/usr/local/lib")
find_library(AVCODEC_LIB NAMES avcodec PATHS "/usr/local/lib")
find_library(XCB_SHM_LIB NAMES xcb-shm PATHS "/usr/local/lib")
find_library(XCB_LIB NAMES xcb PATHS "/usr/local/lib")
find_library(X11_LIB NAMES X11 PATHS "/usr/local/lib")
find_library(SDL_LIB NAMES SDL PATHS "/usr/local/lib")
find_library(BZ2_LIB NAMES bz2 PATHS "/usr/local/lib")
find_library(Z_LIB NAMES z PATHS "/usr/local/lib")
find_library(AVUTIL_LIB NAMES avutil PATHS "/usr/local/lib")
find_library(RT_LIB NAMES rt PATHS "/usr/local/lib")
find_library(M_LIB NAMES m PATHS "/usr/local/lib")

target_link_libraries(server ${PTHREAD_LIB} 
                             ${OPENCV_CORE_LIB} 
                             ${OPENCV_HIGHGUI_LIB} 
                             ${OPENCV_IMGPROC_LIB} 
                             ${OPENCV_VIDEO_LIB}
                             ${BOOST_THREAD_LIB} 
                             ${BOOST_SYSTEM_LIB} 
                             ${CVDRONE_LIB} 
                             ${AVDEVICE_LIB} 
                             ${AVFILTER_LIB} 
                             ${SWSCALE_LIB} 
                             ${AVFORMAT_LIB} 
                             ${AVCODEC_LIB} 
                             ${XCB_SHM_LIB} 
                             ${XCB_LIB} 
                             ${X11_LIB} 
                             ${SDL_LIB} 
                             ${BZ2_LIB} 
                             ${Z_LIB} 
                             ${AVUTIL_LIB} 
                             ${RT_LIB} 
                             ${M_LIB} )
