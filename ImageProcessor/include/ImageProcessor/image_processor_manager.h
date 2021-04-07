#ifndef _IMAGE_PROCESSOR_MANAGER__H__
#define _IMAGE_PROCESSOR_MANAGER__H__

#include <cstdlib>
#include <iostream>
#include <memory>
#include <opencv2/core/core.hpp>
#include <opencv2/core/fast_math.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <string>
#include <variant>
#include <vector>
namespace Multicamera {
namespace ImageProcessor {

struct DetectorParamsBase {
  const double scale_factor = 1.0; // Need to be > 1
  const int min_neighbors = 2;
};

struct ImageProcessorManager {
  using EyesRoiContainer = std::vector<cv::Rect>;
  explicit ImageProcessorManager(std::string_view face_haar_input_file,
                                 std::string_view face_eyes_input_file,
                                 const DetectorParamsBase &face_params,
                                 const DetectorParamsBase &eye_params)
      : face_cascade_(std::string(face_haar_input_file)),
        eyes_cascade_(std::string(face_eyes_input_file)),
        face_params_(face_params), eye_params_(eye_params) {}

  bool CheckClassifiers() const noexcept {
    return (!face_cascade_.empty()) && (!eyes_cascade_.empty());
  }

  bool CheckFaceClasifier() const noexcept { return !face_cascade_.empty(); }

  bool CheckEyeClasifier() const noexcept { return !eyes_cascade_.empty(); }

  bool FacesRoiIsEmpty() const noexcept { return faces_points_.empty(); }

  bool Detect(const cv::Mat &frame) {
    faces_points_.clear();
    cv::Mat frame_gray;
    cv::Mat out_frame = frame;
    cvtColor(frame, frame_gray, cv::COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);
    //-- Detect faces
    std::vector<cv::Rect> faces;
    face_cascade_.detectMultiScale(frame_gray, faces, face_params_.scale_factor,
                                   face_params_.min_neighbors);

    for (const auto &face : faces) {
      cv::Point center(face.x + face.width / 2, face.y + face.height / 2);
      // For Debugging
      cv::ellipse(out_frame, center, cv::Size(face.width / 2, face.height / 2),
                  0, 0, 360, cv::Scalar(255, 0, 255), 4);
      cv::Mat face_roi = frame_gray(face);
      //-- In each face, detect eyes
      std::vector<cv::Rect> eyes;

      eyes_cascade_.detectMultiScale(face_roi, eyes, eye_params_.scale_factor,
                                     eye_params_.min_neighbors);

      for (const auto &eye : eyes) {
        cv::Point eye_center(face.x + eye.x + eye.width / 2,
                             face.y + eye.y + eye.height / 2);
        const int radius = cvRound((eye.width + eye.height) * 0.25);
        cv::circle(out_frame, eye_center, radius, cv::Scalar(255, 0, 0), 4);
      }
      faces_points_.push_back(make_tuple(face, eyes));
    }
    const int number = std::rand() % 10;
    cv::imwrite("test_output" + std::to_string(number) + ".jpg", out_frame);

    return (!faces_points_.empty());
  }

  cv::CascadeClassifier face_cascade_;
  cv::CascadeClassifier eyes_cascade_;
  std::vector<std::tuple<cv::Rect, EyesRoiContainer>>
      faces_points_; // TODO: Optimize this

  const DetectorParamsBase face_params_{};
  const DetectorParamsBase eye_params_{};
};

} // namespace ImageProcessor
} // namespace Multicamera
#endif
