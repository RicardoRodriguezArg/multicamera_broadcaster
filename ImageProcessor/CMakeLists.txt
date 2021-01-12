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


find_package(OpenCV REQUIRED)
find_package(Threads REQUIRED)
find_package(glog REQUIRED)
find_package(gflags REQUIRED)

add_library(${PROJECT_NAME} ${SRCS} ${HDRS})
add_library(MCB::IMAGE_PROCESSOR_LIB ALIAS ${PROJECT_NAME})
#INCLUDE_DIR for our target
target_include_directories(${PROJECT_NAME}
    PUBLIC 
        $<INSTALL_INTERFACE:include>#for interface    
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>#for building
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(${PROJECT_NAME} PRIVATE -Werror -Wpedantic )

# model dependencies
#this target will export the following dependencies
target_link_libraries( ${PROJECT_NAME} PUBLIC 
                                              ${OpenCV_LIBS}
                                              ${CMAKE_THREAD_LIBS_INIT}
                                              ${GLOG_LIBRARIES} glog::glog
                                              ${GFLAGS_LIBRARIES}
                      )
#export our target
include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}-export    #export -> ImageProcessor-export
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
#install the exported target
install(EXPORT ${PROJECT_NAME}-targets
  FILE
    ${PROJECT_NAME}Targets.cmake
  NAMESPACE
    MCB::IMAGE_PROCESSOR_LIB::
  DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)



