project(Application)
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
file(GLOB HDRS "./include/Application/*.h")
#Clang Tidy checks
set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)
#Add Dependencies
#####################################

find_package(OpenCV REQUIRED)
find_package(Threads REQUIRED)
find_package(glog REQUIRED)
find_package(gflags REQUIRED)
include_directories(
../VideoController/
../VideoController/include
../ImageProcessor/
../ImageProcessor/include
)
#find_package(VideoController HINTS "${PROJECT_BINARY_DIR}/../VideoController/generated" REQUIRED)

add_executable(${PROJECT_NAME} ${SRCS} ${HDRS})


target_include_directories(${PROJECT_NAME}
    PUBLIC 
        $<INSTALL_INTERFACE:include>#for interface
        $<INSTALL_INTERFACE:include/Application>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>#for building
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Application
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)



# Link
target_link_libraries( ${PROJECT_NAME} PUBLIC ${OpenCV_LIBS} glog::glog)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wpedantic -O3)


