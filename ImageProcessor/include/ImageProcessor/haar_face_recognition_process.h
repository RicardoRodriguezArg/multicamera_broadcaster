#ifndef _HAAR_FACES_RECOGNITION_PROCESS__H__
#define _HAAR_FACES_RECOGNITION_PROCESS__H__
#include <algorithm>
#include <vector>
#include <exception>
#include "image_processor_interface.h"
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"

namespace Multicamera {
namespace FaceRecognition{

struct HaarFaceRecognitionProcess : ImageProcessBase<HaarFaceRecognitionProcess> {

  constexpr explicit HaarFaceRecognitionProcess(std::unique_ptr<cv::CascadeClassifier> && clasifier) noexcept
  :classifiers_(std::move(clasifier))
  {
  }
  
  ImageProcessorResult process(ImageProcessorIO&& input_data) noexcept{ 
      const auto input_frame = std::get<FrameRGB>(input_data).frame_; 
      cv::Mat frame_gray;
      cv::cvtColor( input_frame, frame_gray, cv::COLOR_BGR2GRAY );
      cv::equalizeHist( frame_gray, frame_gray );
      std::vector<cv::Rect> faces_roi;
      ImageProcessorResult result{};
      classifiers_.detectMultiScale( frame_gray, faces_roi );
      return {{faces}, {}, frame_gray};
   }
  

};
}
} // namespace Multicamera
#endif
