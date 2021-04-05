cmake_minimum_required(VERSION 3.5)
project(image_processor VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

option(BUILD_DEBUG_MODE "Build for debugging output cv algorithms" OFF)
option(BUILD_WITH_TESTS "Build with units tests" OFF)

list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)

file(GLOB SRCS "src/*.cpp")
file(GLOB HDRS "include/Image_Processor/*.h")
#Clang Tidy checks
set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*,-header-filter=.*)
#Add Dependencies
#####################################
find_package(OpenCV REQUIRED)
find_package(Threads REQUIRED)
find_package(glog REQUIRED)
find_package(gflags REQUIRED)

add_library(${PROJECT_NAME}Lib ${SRCS} ${HDRS})
add_executable(${PROJECT_NAME}_bin ${SRCS} ${HDRS} src/main.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include
		    ${CMAKE_CURRENT_SOURCE_DIR}/include/Image_Processor
		    ${OpenCV_INCLUDE_DIRS}
)


target_include_directories(${PROJECT_NAME}Lib
    PUBLIC 
        $<INSTALL_INTERFACE:include>#for interface
        $<INSTALL_INTERFACE:include/Image_Processor>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>#for building
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Image_Processor
    ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src

        
)



# model dependencies
#this target will export the following dependencies
target_link_libraries( ${PROJECT_NAME}Lib PUBLIC 
                                              ${OpenCV_LIBS}
                                              ${CMAKE_THREAD_LIBS_INIT}
                                              ${GLOG_LIBRARIES}
                                              ${GFLAGS_LIBRARIES}
                      )
                      
target_compile_options(${PROJECT_NAME}Lib PRIVATE -Wall -Werror -Wpedantic -O3)

target_compile_definitions(${PROJECT_NAME}Lib PRIVATE DEBUG=1 )

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources/ DESTINATION ${CMAKE_BINARY_DIR}/resources)
#for testing
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources/ DESTINATION ${CMAKE_BINARY_DIR}/test/resources)

#export our target

#set install dir variable
include(GNUInstallDirs)

set (TARGET_EXPORT_CMAKE_FILENAME ${PROJECT_NAME}Targets)

install(TARGETS ${PROJECT_NAME}Lib
         EXPORT  ${TARGET_EXPORT_CMAKE_FILENAME}
         LIBRARY DESTINATION lib/
       )
         
install(EXPORT		${TARGET_EXPORT_CMAKE_FILENAME}
        FILE   		${TARGET_EXPORT_CMAKE_FILENAME}.cmake
        NAMESPACE	${PROJECT_NAME}::
        DESTINATION	cmake/
       )


include(CMakePackageConfigHelpers)

set (CONFIG_INPUT ./cmake/${PROJECT_NAME}Config.cmake.in)
set (CONFIG_FILE ${PROJECT_NAME}Config.cmake)
set (VERSION_FILE ${PROJECT_NAME}Config.cmake)

configure_package_config_file( ${CONFIG_INPUT}
    ${CMAKE_CURRENT_BINARY_DIR}/${CONFIG_FILE}
    INSTALL_DESTINATION cmake/
    PATH_VARS TARGET_EXPORT_CMAKE_FILENAME
)

write_basic_package_version_file(
	${CMAKE_CURRENT_BINARY_DIR}/${VERSION_FILE}
	VERSION ${PACKAGE_VERSION}
        COMPATIBILITY AnyNewerVersion
)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${VERSION_FILE}
              ${CMAKE_CURRENT_BINARY_DIR}/${CONFIG_FILE}
        DESTINATION cmake/
        )


## Add test
enable_testing()
#add_subdirectory(test)


