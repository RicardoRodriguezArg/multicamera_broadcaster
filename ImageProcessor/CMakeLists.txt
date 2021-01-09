project(ImageProcessor)
cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 20)
set(SRCS ${PROJECT_NAME}_SRCS)
file(GLOB SRCS "./src/*.cpp")
file(GLOB HDRS "./include/ImageProcessor/*.h")
#Clang Tidy checks
set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)
#Add Dependencies
#####################################
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../cmake")

find_package(OpenCV REQUIRED)
find_package(Threads REQUIRED)
find_package(glog REQUIRED)
find_package(gflags REQUIRED)

add_executable(${PROJECT_NAME} ${SRCS} ${HDRS})
add_executable(MCB::IMAGE_PROCESSOR_LIB ALIAS ${PROJECT_NAME})
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
