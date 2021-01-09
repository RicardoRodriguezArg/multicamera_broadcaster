#ifndef _HAAR_FACE_RECOGNITION_PROCESS__H__
#define _HAAR_FACE_RECOGNITION_PROCESS__H__
#include <algorithm>
#include <vector>
#include "image_processor_interface.h"
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
/*
#include <opencv2/core/core.hpp>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
*/
namespace Multicamera {
namespace FaceRecognition{

struct HaarFaceRecognitionProcess : ImageProcessBase<HaarFaceRecognitionProcess> {
  enum class HaarInputType : short int
  {
    FACES,
    EYES
  }
  using HaarDetectorUnit = std::tuple<HaarInputType, std::string_view>;
  using HaarDetectorUnitContainer = std::vector<HaarDetectorUnit>;
  using CascadeClassifierContainer = 
  
  explicit HaarFaceRecognitionProcess( HaarDetectorUnitContainer && input_haar_config) noexcept
  {
    CreateClassifier(std::move(input_haar_config));
  }
  
  void CreateClassifier(HaarDetectorUnitContainer && input_configuration) noexcept
  {
  image_processors_results_.reserve(input_configuration.size());
   const auto clousere_lambda = [this](const auto && input_tuple) mutable
     {
       cv::cv::CascadeClassifier classifier{std::get<std::string_view>(input_tuple)};
       if (!classifier.empty())
       {
       classifiers_.emplace_back({
                                  std::get<HaarInputType>(input_tuple),
                                  std::move(classifier)
                                  });
       }
       
     };
     
     std::for_each(std::cbegin(input_configuration), std::cend(input_configuration), clousere_lambda);
  }
  
  
  template <typename Input> 
  bool process(const Input& input_frame) { 
      cv::Mat frame_gray;
      cv::cvtColor( input_frame, frame_gray, COLOR_BGR2GRAY );
      cv::equalizeHist( frame_gray, frame_gray );
      //-- Detect faces
      std::vector<cv::Rect> faces;
      const auto face_iterator = get_classifier_iterator(HaarInputType::FACES);
      if (face_iterator==classifiers_.cend())
      {
	return false;
      }

    *face_iterator.detectMultiScale( frame_gray, faces );
     //-- In each face, detect eyes
     std::vector<cv::Rect> eyes;
     const auto eye_detector_iterator = get_classifier_iterator(HaarInputType::EYES);
     std::transform(faces.cbegin(), faces.cend(), std::back_inserter(eyes), [](const auto &face){
             cv::Point center( face.x + face.width/2, face.y + face.height/2 );
            cv::ellipse( input_frame, center, Size( face.width/2, face.height/2 ), 0, 0, 360, 			cv::Scalar( 255, 0, 255 ), 4 );
        cv::Mat faceROI = frame_gray( face );
                std::vector<cv::Rect> eyes;
        *eye_detector_iterator.detectMultiScale( faceROI, eyes );


});
    
   }
   
   auto get_classifier_iterator(HaarInputType classifier_wanted) noexcept
    {
return classifiers_.find_if(classifiers_.cbegin(), classifiers_.cend(), [this, &classifier_wanted](const auto & input_tuple)
    {
     return (std::get<HaarInputType>(input_tuple)==classifier_wanted);
    });
    }

  std::vector<ImageProcessorResult> image_processors_results_ = {};
  std::vector<std::tuple<HaarInputType, cv::CascadeClassifier>> classifiers_ = {};
};
}
} // namespace Multicamera
#endif
