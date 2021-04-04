cc_library(
    name = "image_processor",
    srcs = glob(["*.cpp"]) + glob(["*.cc"]),
    hdrs = glob(["./include/Image_Processor/*.h"]) + glob(["./include/Image_Processor/*.hpp"]), 
    deps = ["@eigen3//:eigen"],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "kalman_filter_bin",
    srcs = glob(["*.cpp"]) + glob(["*.cc"]),
    deps = [ ":kalman_filter",]

)