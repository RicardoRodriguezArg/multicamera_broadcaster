cmake_minimum_required(VERSION 3.5)
project(imageProcessor VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)

file(GLOB SRCS "src/*.h")
file(GLOB HDRS "include/Image_Processor/*.h")
#Clang Tidy checks
#set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)
#Add Dependencies
#####################################


find_package(OpenCV REQUIRED)
find_package(Threads REQUIRED)
find_package(glog REQUIRED)
find_package(gflags REQUIRED)

add_library(${PROJECT_NAME} ${SRCS} ${HDRS})
add_executable(${PROJECT_NAME}_bin ${SRCS} ${HDRS} src/main.cpp)
add_library(IMAGE_PROCESSOR_LIB ALIAS ${PROJECT_NAME})
#INCLUDE_DIR for our target
#extrange need to add this explicity for Raspy
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include
${CMAKE_CURRENT_SOURCE_DIR}/include/Image_Processor
)
target_include_directories(${PROJECT_NAME}
    PUBLIC 
        $<INSTALL_INTERFACE:include>#for interface    
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>#for building
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Image_Processor
    ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src

        
)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wpedantic )

# model dependencies
#this target will export the following dependencies
target_link_libraries( ${PROJECT_NAME} PUBLIC 
                                              ${OpenCV_LIBS}
                                              ${CMAKE_THREAD_LIBS_INIT}
                                              ${GLOG_LIBRARIES} glog::glog
                                              ${GFLAGS_LIBRARIES}
                      )
#export our target

#set install dir variable
include(GNUInstallDirs)

set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/ImageProcessor)

message(STATUS "Install Configuration Directory: ${INSTALL_CONFIGDIR}")

install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}-targets    #export -> ImageProcessor-export
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ImageProcessor/include
)


set_target_properties(${PROJECT_NAME} PROPERTIES EXPORT_NAME ImageProcessor)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
message(STATUS "Headers to export: ${HDRS}")
install(FILES ${HDRS} DESTINATION include/)
#Install the config, configversion and custom find modules
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/ImageProcessorConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/ImageProcessorConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)
#
#install the exported target
install(EXPORT ${PROJECT_NAME}-targets
  FILE
    ImageProcessorTargets.cmake
  NAMESPACE
    IMAGE_PROCESSOR_LIB::
  DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
	${CMAKE_CURRENT_BINARY_DIR}/ImageProcessorConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/ImageProcessorConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/ImageProcessorConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)



#Exporting for the build  This steps are necessary for exporting the target
#inside the build tree
export(EXPORT ${PROJECT_NAME}-targets
    FILE ${CMAKE_CURRENT_BINARY_DIR}/ImageProcessorTargets.cmake
    NAMESPACE IMAGE_PROCESSOR_LIB::)

#Register package in user's package registry
export(PACKAGE ImageProcessor)

#############################################
## Add test
#enable_testing()
#add_subdirectory(test)


