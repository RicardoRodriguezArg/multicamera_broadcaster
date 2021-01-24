#ifndef _IMAGE_PROCESSOR_INTERFACE__H__
#define _IMAGE_PROCESSOR_INTERFACE__H__
#include <memory>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <variant>
#include <vector>

namespace Multicamera {
namespace ImageProcessor {

struct FrameGrey {
  cv::Mat frame_ = {};
};

struct FrameRGB {
  cv::Mat frame_ = {};
};
struct EyesRoi {
  std::vector<cv::Rect> roi_;
};

struct FaceRoi {
  std::vector<cv::Rect> roi_;
};

using ImageProcessorIO = std::variant<FaceRoi, EyesRoi, FrameRGB, FrameGrey>;

struct ImageProcessorIORArray {
  std::array<ImageProcessorIO, 4> image_properties;
};

template <typename Derived> struct ImageProcessBase {

  ImageProcessorIORArray process(ImageProcessorIO input_data) noexcept {
    return static_cast<Derived *>(this)->implementation(input_data);
  }

  std::unique_ptr<cv::CascadeClassifier> classifiers_;
};

} // namespace ImageProcessor
} // namespace Multicamera
#endif
