#ifndef _VIDEO_CONTROLLER_H__
#define _VIDEO_CONTROLLER_H__
#include <atomic>
#include <ctime>
#include <iostream>
#include <memory>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <thread>

namespace MultiCamera {
namespace VideoController {
namespace {
static constexpr int RASPI_WEB_CAM = 0;
static constexpr int MAX_RETRY_ATTEMP = 100;
}  // namespace

template <typename ImageProcessor>
struct VideoManager {
  explicit VideoManager(
      std::unique_ptr<ImageProcessor> image_processor = nullptr)
      : image_processor_(std::move(image_processor)), capture_device_(RASPI_WEB_CAM) {}

  ~VideoManager() {
    stop();
    if(was_launched_)
    {
    video_thread_.join();
    }
  }

  bool start() {
    const bool is_valid_init = init();
    std::cout <<"Init Video From Raspy"<< std::boolalpha << is_valid_init<<std::endl;
    if (!is_valid_init) {
      return is_valid_init;
    }
    video_thread_ = std::thread(&VideoManager::start_thread, this);
    was_launched_ = true;
    is_working_ = true;
    return was_launched_.load();
  }

  void stop() { is_working_ = false; }

 private:
  void start_thread() {
    int retry_capture_attemp{0};
    while (is_working_) {
      capture_frame_.release();
      if (!capture_device_.read(capture_frame_)) {
        ++retry_capture_attemp;
        if (retry_capture_attemp > MAX_RETRY_ATTEMP) {
          is_working_ = false;
        }
      } else {
        retry_capture_attemp = 0;
#if IMAGE_PROCESSOR_HAAR_DEBUG
        image_processor_->Detect(capture_frame_);
        // show the frame in the created window
        cv::imshow("Default Haar CV DEBUG ", capture_frame_);
#elif IMAGE_PROCESSOR_HAAR
        image_processor_->Detect(capture_frame_);
#endif
      }
    }
  }

  bool init() {
    if (!capture_device_.isOpened()) {
      return false;
    }
    fps_ = capture_device_.get(cv::CAP_PROP_FPS);
    return true;
  }

  double fps_{0.0};
  std::thread video_thread_;
  std::atomic<bool> is_working_{false};
  std::atomic<bool> was_launched_{false};
  cv::Mat capture_frame_{};
  const std::unique_ptr<ImageProcessor> image_processor_;
  cv::VideoCapture capture_device_;  // capture the video from webcam
};
}  // namespace VideoController
}  // namespace MultiCamera
#endif
