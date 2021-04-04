cc_library(
    name = "image_processor_lib",
    hdrs = glob(["include/*.h", "include/*.hpp"]),
    deps = ["@opencv//:opencv4"],
    visibility = ["//visibility:public"],
)

cc_binary(
name="image_processor_bin",
srcs = glob(["src/*.cpp", "src/*.cc",]),
deps = [":image_processor_lib"],
)

