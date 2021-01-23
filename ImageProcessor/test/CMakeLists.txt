find_package(GTest QUIET)
# Now simply link against gtest as needed. Eg
add_executable(image_processor_test main.cpp)
find_package(ImageProcessor REQUIRED)#This brings the target
message (STATUS "ImageProcessor Include Directories: ${ImageProcessor_DIR}")
#include_directories(${ImageProcessor_DIR})
target_link_libraries(image_processor_test gtest_main IMAGE_PROCESSOR_LIB::ImageProcessor)

add_test(NAME ImageProcessor_test
    COMMAND ImageProcessor_test)
