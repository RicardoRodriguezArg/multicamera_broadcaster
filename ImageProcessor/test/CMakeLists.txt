project(image_processor_test VERSION 1.0.0 LANGUAGES CXX)
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
include_directories(../include/ImageProcessor
                    ${OpenCV_INCLUDE_DIRS}
                    ${GTEST_INCLUDE_DIR}
)



add_executable(${PROJECT_NAME} main.cpp face_recognition_tests.cpp)
target_link_libraries(image_processor_test 
			gtest
			gtest_main
			${GTEST_BOTH_LIBRARIES}
			${OpenCV_LIBS}
                        ${CMAKE_THREAD_LIBS_INIT}
			)

message (STATUS "Copying images files to testing directory: ${CMAKE_BINARY_DIR}/test/images")
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources/ DESTINATION ${CMAKE_BINARY_DIR}/test/images)

add_test(NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME})
