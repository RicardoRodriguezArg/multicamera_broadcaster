project(VideoController VERSION 1.0.0 LANGUAGES CXX)

cmake_minimum_required(VERSION 3.5)


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
add_library(${PROJECT_NAME}Lib ${SRCS} ${HDRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include
		    ${CMAKE_CURRENT_SOURCE_DIR}/include/VideoController
		    ${OpenCV_INCLUDE_DIRS}
)
#INCLUDE_DIR for our target
target_include_directories(${PROJECT_NAME}
    PUBLIC 
        $<INSTALL_INTERFACE:include>#for interface
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>#for building
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/VideoController>#for building
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
	${CMAKE_CURRENT_SOURCE_DIR}/include#for building
        ${CMAKE_CURRENT_SOURCE_DIR}/include/VideoController#for building
)
# Link
target_link_libraries( ${PROJECT_NAME} PUBLIC ${OpenCV_LIBS} glog::glog)
target_link_libraries( ${PROJECT_NAME}Lib PUBLIC ${OpenCV_LIBS} glog::glog)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wpedantic -O3)
target_compile_options(${PROJECT_NAME}Lib PRIVATE -Wall -Werror -Wpedantic -O3)
#-----------------------------------------------------------------------------
#export our target
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

install(
    DIRECTORY "include/VideoController"
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

