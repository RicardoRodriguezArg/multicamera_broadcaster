#ifndef _IMAGE_PROCESSOR_INTERFACE__H__
#define _IMAGE_PROCESSOR_INTERFACE__H__
#include <variant>
#include <vector>
#include <memory>

namespace Multicamera {
namespace ImageProcessor{

struct FrameGrey
{
cv::Mat frame_ ={};
};

struct FrameRGB
{
cv::Mat frame_ ={};
};
struct EyesRoi
{
std::vector<cv::Rect> roi_;
};

struct FaceRoi
{
 std::vector<cv::Rect> roi_;
};



template<typename >
using ImageProcessorIO = std::variant<FaceRoi, EyesRoi, FrameRGB, FrameGrey>;

template <typename Derived>
struct ImageProcessBase {

  ImageProcessorIO process(ImageProcessorIO input_data) noexcept{ 
  return static_cast<Derived*>(this)->implementation(input_data);
  }
  
  std::unique_ptr<cv::CascadeClassifier> classifiers_ = std::nullptr;
};

}
} // namespace Multicamera
#endif
