cmake_minimum_required(VERSION 2.8.4)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/)
set(USER_LIB_PATH "/usr/local/lib")
set(BOOST_LIB_PATH "/opt/boost_1_57_0/lib")
set(CVDRONE_LIB_PATH "/opt/cvdrone/lib")

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

file(GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR}/includes/*.hpp
                  ${PROJECT_SOURCE_DIR}/includes/*.h)

add_executable(server ${SOURCES} ${HEADERS})
#add_executable(client test_client.c)

include_directories(../includes
                    ../includes/core
                    /opt/boost_1_57_0/include
                    /opt/cvdrone/include
                    /usr/local/include/opencv
                    /usr/local/include/opencv2)

# pthread
find_library(PTHREAD_LIB NAMES pthread PATHS ${USER_LIB_PATH})

# opencv
find_library(OPENCV_CORE_LIB NAMES opencv_core PATHS ${USER_LIB_PATH})
find_library(OPENCV_HIGHGUI_LIB NAMES opencv_highgui PATHS ${USER_LIB_PATH})
find_library(OPENCV_IMGPROC_LIB NAMES opencv_imgproc PATHS ${USER_LIB_PATH})
find_library(OPENCV_VIDEO_LIB NAMES opencv_video PATHS ${USER_LIB_PATH})

# boost
find_library(BOOST_THREAD_LIB NAMES boost_thread PATHS ${BOOST_LIB_PATH})
find_library(BOOST_SYSTEM_LIB NAMES boost_system PATHS ${BOOST_LIB_PATH})

# cvdrone
find_library(CVDRONE_LIB NAMES cvdrone PATHS ${CVDRONE_LIB_PATH})

# fmpeg libs
find_library(AVDEVICE_LIB NAMES avdevice PATHS ${USER_LIB_PATH})
find_library(AVFILTER_LIB NAMES avfilter PATHS ${USER_LIB_PATH})
find_library(SWSCALE_LIB NAMES swscale PATHS ${USER_LIB_PATH})
find_library(AVFORMAT_LIB NAMES avformat PATHS ${USER_LIB_PATH})
find_library(AVCODEC_LIB NAMES avcodec PATHS ${USER_LIB_PATH})
find_library(XCB_SHM_LIB NAMES xcb-shm PATHS ${USER_LIB_PATH})
find_library(XCB_LIB NAMES xcb PATHS ${USER_LIB_PATH})
find_library(X11_LIB NAMES X11 PATHS ${USER_LIB_PATH})
find_library(SDL_LIB NAMES SDL PATHS ${USER_LIB_PATH})
find_library(BZ2_LIB NAMES bz2 PATHS ${USER_LIB_PATH})
find_library(Z_LIB NAMES z PATHS ${USER_LIB_PATH})
find_library(AVUTIL_LIB NAMES avutil PATHS ${USER_LIB_PATH})
find_library(RT_LIB NAMES rt PATHS ${USER_LIB_PATH})
find_library(M_LIB NAMES m PATHS ${USER_LIB_PATH})

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
