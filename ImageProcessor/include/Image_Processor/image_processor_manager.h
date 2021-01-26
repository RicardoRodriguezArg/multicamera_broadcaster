#ifndef _IMAGE_PROCESSOR_MANAGER__H__
#define _IMAGE_PROCESSOR_MANAGER__H__

#include <memory>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <string>
#include <variant>
#include <vector>

namespace Multicamera {
namespace ImageProcessor {

struct ImageProcessorManager {
  explicit ImageProcessorManager(std::string_view face_haar_input_file,
                                 std::string_view face_eyes_input_file)
      : face_cascade_(std::string(face_haar_input_file)),
        eyes_cascade_(std::string(face_eyes_input_file)) {}

  void Detect(const cv::Mat &frame) {
    faces_points_.clear();
    eyes_points_.clear();
    cv::Mat frame_gray;
    cvtColor(frame, frame_gray, cv::COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);
    //-- Detect faces
    std::vector<cv::Rect> faces;
    face_cascade_.detectMultiScale(frame_gray, faces);
    for (const auto &face : faces) {
      cv::Point center(face.x + face.width / 2, face.y + face.height / 2);
      cv::Mat face_roi = frame_gray(face);
      //-- In each face, detect eyes
      std::vector<cv::Rect> eyes;
      eyes_cascade_.detectMultiScale(face_roi, eyes);
      for (const auto &eye : eyes) {
        cv::Point eye_center(face.x + eye.x + eye.width / 2,
                             face.y + eye.y + eye.height / 2);
      }
    }
  }

  cv::CascadeClassifier face_cascade_;
  cv::CascadeClassifier eyes_cascade_;
  std::vector<cv::Point> faces_points_;
  std::vector<cv::Point> eyes_points_;
};

} // namespace ImageProcessor
} // namespace Multicamera
#endif
