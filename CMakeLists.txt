cmake_minimum_required(3.0)
project(Communications)
include(GNUInstallDirs)
#Build Type
IF(NOT CMAKE_BUILD_TYPE )
   SET( CMAKE_BUILD_TYPE "Release" )
ENDIF()

add_definitions(-Wall -Wextra -pedantic)
include (cmake/GMockConfig.cmake)
find_package(GTest REQUIRED)
add_library(GTest INTERFACE IMPORTED)
set_property(TARGET GTest PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${GTEST_INCLUDE_DIRS})

find_package(Threads REQUIRED)
add_library(Threads INTERFACE IMPORTED)
find_package(OpenCV REQUIRED)
add_library(OpenCV INTERFACE IMPORTED)
set_property(TARGET OpenCV PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${OpenCV_INCLUDE_DIRS})
find_package(gflags REQUIRED)
#add_library(gflags INTERFACE IMPORTED)
find_package(glog REQUIRED)
add_library(glog INTERFACE IMPORTED)

add_subdirectory(ImageProcessor)
add_subdirectory(VideoController)
add_subdirectory(Applicaton)

