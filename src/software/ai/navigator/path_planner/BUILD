package(default_visibility = ["//software/ai:__subpackages__"])

cc_library(
    name = "path_planner",
    hdrs = ["path_planner.h"],
    deps = [
        "//software/ai/navigator/obstacle",
        "//software/geom",
        "//software/new_geom:linear_spline2d",
        "//software/new_geom/util:distance",
    ],
)

cc_library(
    name = "straight_line_path_planner",
    srcs = ["straight_line_path_planner.cpp"],
    hdrs = ["straight_line_path_planner.h"],
    deps = [":path_planner"],
)

cc_test(
    name = "straight_line_path_planner_test",
    srcs = ["straight_line_path_planner_test.cpp"],
    deps = [
        ":straight_line_path_planner",
        "@gtest//:gtest_main",
    ],
)

cc_library(
    name = "theta_star_path_planner",
    srcs = ["theta_star_path_planner.cpp"],
    hdrs = ["theta_star_path_planner.h"],
    deps = [
        ":path_planner",
    ],
)

cc_library(
    name = "no_path_test_path_planner",
    srcs = ["no_path_test_path_planner.cpp"],
    hdrs = ["no_path_test_path_planner.h"],
    deps = [
        ":path_planner",
    ],
)

cc_library(
    name = "one_point_path_test_path_planner",
    srcs = ["one_point_path_test_path_planner.cpp"],
    hdrs = ["one_point_path_test_path_planner.h"],
    deps = [
        ":path_planner",
    ],
)

cc_test(
    name = "theta_star_path_planner_test",
    srcs = ["theta_star_path_planner_test.cpp"],
    deps = [
        ":theta_star_path_planner",
        "//software/ai/navigator/obstacle:obstacle_factory",
        "//software/test_util",
        "//software/world:field",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "path_planner_test",
    srcs = ["path_planner_test.cpp"],
    deps = [
        ":path_planner",
        ":straight_line_path_planner",
        ":theta_star_path_planner",
        "//software/ai/navigator/obstacle:obstacle_factory",
        "//software/test_util",
        "@gtest//:gtest_main",
    ],
)
