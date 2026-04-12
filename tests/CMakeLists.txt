find_package(Catch2 REQUIRED)

add_executable(test_unionfind test_unionfind.cpp)
add_executable(test_convex_hull test_convex_hull.cpp)
add_executable(test_ray_casting test_ray_casting.cpp)
add_executable(test_segment_tree test_segment_tree.cpp)
add_executable(test_big_integer test_big_integer.cpp)

target_link_libraries(test_unionfind PRIVATE Catch2::Catch2WithMain algorithms)
target_link_libraries(test_convex_hull PRIVATE Catch2::Catch2WithMain algorithms)
target_link_libraries(test_ray_casting PRIVATE Catch2::Catch2WithMain algorithms)
target_link_libraries(test_segment_tree PRIVATE Catch2::Catch2WithMain algorithms)
target_link_libraries(test_big_integer PRIVATE Catch2::Catch2WithMain algorithms)

include(CTest)
include(Catch)

catch_discover_tests(test_unionfind)
catch_discover_tests(test_convex_hull)
catch_discover_tests(test_ray_casting)
catch_discover_tests(test_segment_tree)
catch_discover_tests(test_big_integer)

