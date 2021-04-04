get_filename_component(IMAGEPROCESSOR_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
include(CMakeFindDependencyMacro)

#list(APPEND CMAKE_MODULE_PATH ${IMAGEPROCESSOR_CMAKE_DIR})

#find_dependency(RapidJSON )
#find_dependency(OpenCV )
#OpenCV 
#Threads
#glog
#gflags

#list(REMOVE_AT CMAKE_MODULE_PATH -1)



if(NOT TARGET IMAGE_PROCESSOR_LIB::ImageProcessor)
    message(STATUS "Install Configuration Script----->: ${IMAGEPROCESSOR_CMAKE_DIR}")
    set (ImageProcessor_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include
                        ${CMAKE_CURRENT_SOURCE_DIR}/include/Image_Processor
    )
    include("${IMAGEPROCESSOR_CMAKE_DIR}/ImageProcessorTargets.cmake")
endif()

set(IMAGEPROCESSOR_lIBRARIES TARGET IMAGE_PROCESSOR_LIB::ImageProcessor)
