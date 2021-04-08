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
		    ${CMAKE_CURRENT_SOURCE_DIR}/include/ImageProcessor
		    ${OpenCV_INCLUDE_DIRS}
)


target_include_directories(${PROJECT_NAME}Lib
    PUBLIC 
        $<INSTALL_INTERFACE:include>#for interface
        $<INSTALL_INTERFACE:include/imageProcessor>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>#for building
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/image_processor
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

#this target will export the following dependencies
target_link_libraries( ${PROJECT_NAME}Lib PUBLIC 
                                              ${OpenCV_LIBS}
                                              ${CMAKE_THREAD_LIBS_INIT}
                                              ${GLOG_LIBRARIES}
                                              ${GFLAGS_LIBRARIES}
                      )

target_compile_options(${PROJECT_NAME}Lib PRIVATE -Wall -Werror -Wpedantic -O3)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources/ DESTINATION ${CMAKE_BINARY_DIR}/resources)
#for testing
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources/ DESTINATION ${CMAKE_BINARY_DIR}/test/resources)

#export our target

#set install dir variable
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
set(config_install_dir "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")

# Configuration
set(version_config "${generated_dir}/${PROJECT_NAME}ConfigVersion.cmake")
set(project_config "${generated_dir}/${PROJECT_NAME}Config.cmake")
set(TARGETS_EXPORT_NAME "${PROJECT_NAME}Targets")
set(namespace "${PROJECT_NAME}::")


write_basic_package_version_file(
    "${version_config}" COMPATIBILITY SameMajorVersion
)
configure_package_config_file(
    "cmake/${PROJECT_NAME}Config.cmake.in"
    "${project_config}"
    INSTALL_DESTINATION "${config_install_dir}"
)

install(
    TARGETS ${PROJECT_NAME}Lib
    EXPORT "${TARGETS_EXPORT_NAME}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)
# Headers:
#   * Source/foo/Bar.hpp -> <prefix>/include/foo/Bar.hpp
#   * Source/foo/Baz.hpp -> <prefix>/include/foo/Baz.hpp
install(
    DIRECTORY "include/ImageProcessor"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    FILES_MATCHING PATTERN "*.h"
)

install(
    FILES "${project_config}" "${version_config}"
    DESTINATION "${config_install_dir}"
)

# Config
#   * <prefix>/lib/cmake/Foo/FooTargets.cmake
install(
    EXPORT "${TARGETS_EXPORT_NAME}"
    NAMESPACE "${namespace}"
    DESTINATION "${config_install_dir}"
)

## Add test
enable_testing()
add_subdirectory(test)


