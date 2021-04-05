package(default_visibility = ["//visibility:public"])

MODULES = [
    "calib3d",
    "core",
    "features2d",
    "flann",
    "highgui",
    "imgcodecs",
    "imgproc",
    "ml",
    "videoio",
    "ximgproc",
]

MODULE_DEPS = {
    "calib3d": [
        "core",
        "features2d",
        "flann",
        "imgproc",
    ],
    "features2d": [
        "core",
        "highgui",
        "flann",
    ],
    "flann": ["core"],
    "highgui": [
        "core",
        "videoio",
        "@//cairo",
    ],
    "imgcodecs": [
        "core",
        "imgproc",
        "@//ThirdParty/libjpeg",
        "@//ThirdParty/libtiff",
        "@//ThirdParty/libjbig",
        "@//ThirdParty/libwebp",
    ],
    "imgproc": [
        "core",
        "flann",
    ],
    "ml": ["core"],
    "videoio": [
        "core",
        "imgproc",
        "imgcodecs",
    ],
    "ximgproc": [
        "core",
        "calib3d",
        "imgcodecs",
    ],
}

[
    (
        cc_library(
            name = module,
            srcs = glob(["lib/libopencv_{}.so*".format(module)]),
            hdrs = ["include/opencv4/opencv2/{}.hpp".format(module)] + glob(["include/opencv4/opencv2/{}/.h".format(module)]) +
                   ([
                       "include/opencv4/opencv2/cvconfig.h",
                       "include/opencv4/opencv2/opencv.hpp",
                       "include/opencv4/opencv2/opencv_modules.hpp",
                       "include/opencv4/opencv2/core/hal/interface.h",
                       "include/opencv4/opencv2/highgui/highgui.hpp",
                       "include/opencv4/opencv2/highgui.hpp",
                       "include/opencv4/opencv2/videoio.hpp",
                       "include/opencv4/opencv2/highgui/highgui_c.h",
                       "include/opencv4/opencv2/videoio/videoio_c.h",
                       "include/opencv4/opencv2/calib3d/calib3d.hpp",
                       "include/opencv4/opencv2/calib3d/calib3d_c.h",
                       "include/opencv4/opencv2/calib3d.hpp",
                       "include/opencv4/opencv2/features2d.hpp",
                       "include/opencv4/opencv2/flann/config.h",
                       "include/opencv4/opencv2/flann/miniflann.hpp",
                       "include/opencv4/opencv2/flann/defines.h",
                       "include/opencv4/opencv2/video.hpp",
                       "include/opencv4/opencv2/video/tracking.hpp",
                       "include/opencv4/opencv2/video/background_segm.hpp",
                      
                       "include/opencv4/opencv2/ml.hpp",
                       "include/opencv4/opencv2/ml/ml.inl.hpp",
                   ] if module == "core" else []),
            includes = ["include"],
            deps = MODULE_DEPS[module] if module in MODULE_DEPS else [],
        )
    )
    for module in MODULES
]

# aggregate target - to be removed once all references to this target have been refactored
cc_library(
    name = "opencv",
    deps = MODULES,
)

