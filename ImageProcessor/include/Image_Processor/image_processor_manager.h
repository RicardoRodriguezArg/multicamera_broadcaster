#ifndef _IMAGE_PROCESSOR_MANAGER__H__
#define _IMAGE_PROCESSOR_MANAGER__H__
#include <array>
#include <iostream>
#include <type_traits>
#include "image_processor_interface.h"

namespace Multicamera {
namespace ImageProcessor{
enum class DetectorType : unsigned short{
FACES,
EYES,
BOTH
};

template <typename... Args>
constexpr auto make_array(Args&&... args)
    -> std::array<std::common_type_t<Args...>, sizeof...(Args)> 
{
  return {std::forward<Args>(args)...};
}


template<DetectorType Detector, typename Arguments...>
struct ImageProcessProxy;

template<typename Arguments...>
struct ImageProcessProxy<FACES, typename Arguments...>
{
explicit ImageProcessProxy(Arguments && arguments...):face_recognition_(arguments...)
{}

HaarFaceRecognitionProcess face_recognition_;
}


}
}
#endif
