project(image_processor_test VERSION 1.0.0 LANGUAGES CXX)
find_package(GTest REQUIRED)

find_package(ImageProcessor REQUIRED)#This brings the target
message (STATUS "ImageProcessor Include Directories: ${ImageProcessor_DIR}")
include_directories(${ImageProcessor_DIR} ${OpenCV_INCLUDE_DIRS})


# Now simply link against gtest as needed. Eg
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(image_processor_test gtest_main IMAGE_PROCESSOR_LIB::ImageProcessor)

add_test(NAME ImageProcessor_tests
    COMMAND ImageProcessor_test)
