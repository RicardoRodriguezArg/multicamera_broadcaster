#ifndef _IMAGE_PROCESSOR_MANAGER__H__
#define _IMAGE_PROCESSOR_MANAGER__H__
#include "haar_face_recognition_process.h"
#include "image_processor_interface.h"
#include <array>
#include <iostream>
#include <type_traits>
namespace Multicamera {
namespace ImageProcessor {
enum class DetectorType : unsigned short { FACES, EYES, BOTH };

template <typename... Args>
constexpr auto make_array(Args &&...args)
    -> std::array<std::common_type_t<Args...>, sizeof...(Args)> {
  return {std::forward<Args>(args)...};
}

template <DetectorType Detector, typename... Arguments>
struct ImageProcessProxy;

template <typename... Arguments>
struct ImageProcessProxy<DetectorType::FACES, Arguments...> {
  explicit ImageProcessProxy(Arguments &&...arguments)
      : face_recognition_(std::forward<Arguments>(arguments)...) {}

  HaarFaceRecognitionProcess face_recognition_;
};

} // namespace ImageProcessor
} // namespace Multicamera
#endif
