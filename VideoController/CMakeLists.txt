project(VideoController)
cmake_minimum_required(VERSION 3.5)
option(BUILD_HAAR_DETECTOR "Build Haar Default CV Detector" OFF)
option(BUILD_HAAR_DETECTOR_DEBUG "Build for debug with OpenCv Image viewer" OFF)

if (BUILD_HAAR_DETECTOR)
    add_definitions(-DIMAGE_PROCESSOR_HAAR_DEBUG=1)
    add_definitions(-D0IMAGE_PROCESSOR_HAAR=0)
endif()

if (BUILD_HAAR_DETECTOR_DEBUG)
    add_definitions(-DIMAGE_PROCESSOR_HAAR_DEBUG=0)
    add_definitions(-D0IMAGE_PROCESSOR_HAAR=1)
endif()

set(CMAKE_CXX_STANDARD 20)
set(SRCS ${PROJECT_NAME}_SRCS)
file(GLOB SRCS "./src/*.cpp")
file(GLOB HDRS "./include/VideoController/*.h")
#Clang Tidy checks
set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)
#Add Dependencies
#####################################

find_package(OpenCV REQUIRED)
find_package(Threads REQUIRED)
find_package(glog REQUIRED)
find_package(gflags REQUIRED)
set (CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-as-needed")
add_executable(${PROJECT_NAME} ${SRCS} ${HDRS})
add_executable(MCB::VIDEO_CONTROLLER_LIB ALIAS ${PROJECT_NAME})
#INCLUDE_DIR for our target
target_include_directories(${PROJECT_NAME}
    PUBLIC 
        $<INSTALL_INTERFACE:include>#for interface    
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>#for building
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link
target_link_libraries( ${PROJECT_NAME} PUBLIC ${OpenCV_LIBS} glog::glog)
