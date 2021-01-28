#include "gtest/gtest.h"
#include <Image_Processor/image_processor_manager.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

namespace{
class ImageDetectorFixture : public ::testing::Test
{
 
 protected:

cv::Mat LoadImageOne()
 {
   return cv::imread("./faces_one.jpeg", cv::IMREAD_COLOR); 
 }
 

Multicamera::ImageProcessor::ImageProcessorManager face_recognition_{"./resources/haarcascade_frontalface_alt.xml","./resources/haarcascade_eye_tree_eyeglasses.xml"};
};

TEST_F(ImageDetectorFixture, CheckLoadCHaarClasifierCorreclty) 
{
 	ASSERT_TRUE(face_recognition_.CheckFaceClasifier());
	ASSERT_TRUE(face_recognition_.CheckEyeClasifier());
   ASSERT_TRUE(face_recognition_.CheckClassifiers());

}

TEST_F(ImageDetectorFixture, DetectTwoFacesInTwoImagePictureWhenClassifiersAreLoadedCorrectly)
{
 	ASSERT_TRUE(face_recognition_.CheckFaceClasifier());
	ASSERT_TRUE(face_recognition_.CheckEyeClasifier());
   ASSERT_TRUE(face_recognition_.CheckClassifiers());
   const auto image_one = LoadImageOne();
   ASSERT_TRUE(!image_one.empty());
   ASSERT_TRUE(face_recognition_.Detect(image_one));
   }
}
