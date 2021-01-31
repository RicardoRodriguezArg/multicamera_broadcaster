project(image_processor_test VERSION 1.0.0 LANGUAGES CXX)
find_package(GTest REQUIRED)

find_package(ImageProcessor REQUIRED)#This brings the target
message (STATUS "ImageProcessor Include Directories: ${ImageProcessor_DIR}")
include_directories(${ImageProcessor_DIR} 
                    ${OpenCV_INCLUDE_DIRS}
                    ${GTEST_INCLUDE_DIR}
)



add_executable(${PROJECT_NAME} main.cpp face_recognition_tests.cpp)
target_link_libraries(image_processor_test 
			IMAGE_PROCESSOR_LIB::ImageProcessor
			gtest
			gtest_main
			)

message (STATUS "Copying images files to testing directory: ${CMAKE_BINARY_DIR}/test/images")
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources/ DESTINATION ${CMAKE_BINARY_DIR}/test/images)

add_test(NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME})
