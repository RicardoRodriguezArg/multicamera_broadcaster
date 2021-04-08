#include <VideoController/video_controller.h>
#include <ImageProcessor/image_processor_manager.h>
#include <iostream>

int main() {
  Multicamera::ImageProcessor::DetectorParamsBase face_params{1.3, 3};
  Multicamera::ImageProcessor::DetectorParamsBase eye_params{1.5, 2};
  Multicamera::ImageProcessor::ImageProcessorManager face_recognition{
      "./resources/haarcascade_frontalface_alt.xml",
      "./resources/haarcascade_eye_tree_eyeglasses.xml", face_params,
      eye_params};
      
  //MultiCamera::VideoController<Multicamera::ImageProcessor::ImageProcessorManager> video_controller{};
  return 0;
}
