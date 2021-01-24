#ifndef _HAAR_EYES_RECOGNITION_PROCESS__H__
#define _HAAR_EYES_RECOGNITION_PROCESS__H__
#include "image_processor_interface.h"
#include <algorithm>
#include <vector>

namespace Multicamera {
namespace ImageProcessor {
struct HaarFaceRecognitionProcess
    : /*ImageProcessBase<HaarFaceRecognitionProcess>*/ {

  constexpr explicit HaarFaceRecognitionProcess(
      std::unique_ptr<cv::CascadeClassifier> &&clasifier_string) noexcept
      : classifiers_(std::move(clasifier)) {}

  ImageProcessorIORArray process(ImageProcessorIO input_data) noexcept {
    const auto input_frame = std::get<cv::Mat>(input_data);
    cv::Mat frame_gray;
    cv::cvtColor(input_frame, frame_gray, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(frame_gray, frame_gray);
    std::vector<cv::Rect> faces;
    classifiers_->detectMultiScale(frame_gray, faces);
    ImageProcessorIORArray result{};
    return result;
  }
};
} // namespace ImageProcessor
} // namespace Multicamera
#endif
