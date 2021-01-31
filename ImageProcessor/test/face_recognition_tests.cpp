#include "gtest/gtest.h"
#include <Image_Processor/image_processor_manager.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

namespace {
class ImageDetectorFixture : public ::testing::Test {

protected:
  cv::Mat LoadImageOne(const std::string_view image_file) {
    return cv::imread(std::string{image_file.data(), image_file.size()},
                      cv::IMREAD_COLOR);
  }
};

TEST_F(ImageDetectorFixture, CheckLoadCHaarClasifierCorreclty) {
  Multicamera::ImageProcessor::DetectorParamsBase face_params{1.3, 3};
  Multicamera::ImageProcessor::DetectorParamsBase eye_params{1.5, 2};
  Multicamera::ImageProcessor::ImageProcessorManager face_recognition_{
      "./resources/haarcascade_frontalface_alt.xml",
      "./resources/haarcascade_eye_tree_eyeglasses.xml", face_params,
      eye_params};
  ASSERT_TRUE(face_recognition_.CheckFaceClasifier());
  ASSERT_TRUE(face_recognition_.CheckEyeClasifier());
  ASSERT_TRUE(face_recognition_.CheckClassifiers());
}

TEST_F(
    ImageDetectorFixture,
    DetectOneFaceAndTwoEyesInImagePictureOnMenImageWhenClassifiersAreLoadedCorrectly) {
  Multicamera::ImageProcessor::DetectorParamsBase face_params{1.3, 3};
  Multicamera::ImageProcessor::DetectorParamsBase eye_params{1.5, 2};
  Multicamera::ImageProcessor::ImageProcessorManager face_recognition_{
      "./resources/haarcascade_frontalface_alt.xml",
      "./resources/haarcascade_eye_tree_eyeglasses.xml", face_params,
      eye_params};
  ASSERT_TRUE(face_recognition_.CheckFaceClasifier());
  ASSERT_TRUE(face_recognition_.CheckEyeClasifier());
  ASSERT_TRUE(face_recognition_.CheckClassifiers());
  const auto &image_one = LoadImageOne("./images/man_one_face_happy_path.jpeg");
  ASSERT_TRUE(!image_one.empty());
  ASSERT_TRUE(face_recognition_.Detect(image_one));
  ASSERT_TRUE(!face_recognition_.FacesRoiIsEmpty());
  ASSERT_EQ(face_recognition_.faces_points_.size(), 1U);
  const auto &eyes = std::get<1>(face_recognition_.faces_points_[0]);
  ASSERT_TRUE(eyes.size() >=
              2U); // TODO: Add outlier method for reject redundant rois
}

TEST_F(
    ImageDetectorFixture,
    DetectOneFaceAndTwoEyesInImagePictureOnWomenImageWhenClassifiersAreLoadedCorrectly) {
  Multicamera::ImageProcessor::DetectorParamsBase face_params{1.3, 3};
  Multicamera::ImageProcessor::DetectorParamsBase eye_params{1.5, 2};
  Multicamera::ImageProcessor::ImageProcessorManager face_recognition_{
      "./resources/haarcascade_frontalface_alt.xml",
      "./resources/haarcascade_eye_tree_eyeglasses.xml", face_params,
      eye_params};
  ASSERT_TRUE(face_recognition_.CheckFaceClasifier());
  ASSERT_TRUE(face_recognition_.CheckEyeClasifier());
  ASSERT_TRUE(face_recognition_.CheckClassifiers());
  const auto &image_one =
      LoadImageOne("./images/women_one_face_happy_path.jpeg");
  ASSERT_TRUE(!image_one.empty());
  ASSERT_TRUE(face_recognition_.Detect(image_one));
  ASSERT_TRUE(!face_recognition_.FacesRoiIsEmpty());
  ASSERT_EQ(face_recognition_.faces_points_.size(), 1U);
  const auto &eyes = std::get<1>(face_recognition_.faces_points_[0]);
  ASSERT_TRUE(eyes.size() >=
              2U); // TODO: Add outlier method for reject redundant rois
}

} // namespace
