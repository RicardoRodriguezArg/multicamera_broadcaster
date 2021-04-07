#ifndef _VIDEO_CONTROLLER_H__
#define _VIDEO_CONTROLLER_H__
#include <ctime>
#include <memory>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

namespace MultiCamera {
namespace VideoController {
namespace {
static constexpr int RASPI_WEB_CAM = 0U;
}

template <typename ImageProcessor> struct VideoControllerInfo {
  explicit VideoControllerInfo(
      const std::shared_ptr<ImageProcessor> &image_processor = nullptr)
      : image_processor_(image_processor), capture_device_(RASPI_WEB_CAM) {}

  bool init() {
    if (!capture_device_.isOpened()) {
      return false;
    }
    const double fps = capture_device_.get(cv::CAP_PROP_FPS);
    return true;
  }

  cv::VideoCapture capture_device_; // capture the video from webcam
  const std::shared_ptr<ImageProcessor> image_processor_;
};
} // namespace VideoController
} // namespace StartupName
#endif
