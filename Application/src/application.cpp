#include <VideoController/video_controller.h>
#include <ImageProcessor/image_processor_manager.h>
#include <iostream>
#include <string_view>

namespace {
using ImageProcessorManager = Multicamera::ImageProcessor::ImageProcessorManager;
constexpr std::string_view HAAR_FACE_FILENAME{"./resources/haarcascade_frontalface_alt.xml"};
constexpr std::string_view HAAR_EYE_FILENAME{"./resources/haarcascade_eye_tree_eyeglasses.xml"};
}

int main() {
  Multicamera::ImageProcessor::DetectorParamsBase face_params{1.3, 3};
  Multicamera::ImageProcessor::DetectorParamsBase eye_params{1.5, 2};
  std::cout << "Creating Image Processor" << std::endl;
  auto image_processor_ptr = std::make_unique<ImageProcessorManager>(HAAR_FACE_FILENAME, HAAR_EYE_FILENAME, face_params, eye_params);
  std::cout << "Creating Video Manager" << std::endl;
  MultiCamera::VideoController::VideoManager<ImageProcessorManager> video_controller{std::move(image_processor_ptr)};
  video_controller.start();
  while(1)
  {}
  return 0;
}
