#ifndef _HAAR_FACES_RECOGNITION_PROCESS__H__
#define _HAAR_FACES_RECOGNITION_PROCESS__H__
#include "image_processor_interface.h"
#include <algorithm>
#include <exception>
#include <vector>

namespace Multicamera {
namespace ImageProcessor {

struct HaarFaceRecognitionProcess
    : ImageProcessBase<HaarFaceRecognitionProcess> {

  constexpr explicit HaarFaceRecognitionProcess(
      std::unique_ptr<cv::CascadeClassifier> &&clasifier) noexcept {
    classifiers_ = std::move(clasifier);
  }

  ImageProcessorIORArray process(ImageProcessorIO &&input_data) noexcept {
    const auto input_frame = std::get<FrameRGB>(input_data).frame_;
    cv::Mat frame_gray;
    cv::cvtColor(input_frame, frame_gray, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(frame_gray, frame_gray);
    std::vector<cv::Rect> faces_roi;
    classifiers_->detectMultiScale(frame_gray, faces_roi);
    // ImageProcessorIORArray result{faces_roi, {}, frame_gray};
    ImageProcessorIORArray result{};
    return result;
  }
};
} // namespace ImageProcessor
} // namespace Multicamera
#endif
