project(VideoController)
cmake_minimum_required(3.0)
set(SRCS ${PROJECT_NAME}_SRCS)

file(GLOB SRCS "./src/*.cpp")

add_library(${PROJECT_NAME} ${SRCS})
add_library(MCB::VIDEO_CONTROLLER_LIB ALIAS ${PROJECT_NAME})

# Link
target_link_libraries( ${PROJECT_NAME} PRIVATE ${OpenCV_LIBS} glog::glog)
