#ifndef _IMAGE_PROCESSOR_INTERFACE__H__
#define _IMAGE_PROCESSOR_INTERFACE__H__
#include <variant>
#include <vector>

namespace Multicamera {
namespace ImageProcessor{

using ImageProcessorResult = std::variant<std::vector<cv::Rect>>;

template <typename Derived> struct ImageProcessBase {

  template <typename Input> bool process(Input input_data) { return false; }

  ImageProcessorResult image_processor_result_ = {};
};
}
} // namespace Multicamera
#endif
