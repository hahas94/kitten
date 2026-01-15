find_package(Catch2 REQUIRED)

add_executable(test_unionfind test_unionfind.cpp)
add_executable(test_convex_hull test_convex_hull.cpp)

target_link_libraries(test_unionfind PRIVATE Catch2::Catch2WithMain algorithms)
target_link_libraries(test_convex_hull PRIVATE Catch2::Catch2WithMain algorithms)

include(CTest)
include(Catch)

catch_discover_tests(test_unionfind)
catch_discover_tests(test_convex_hull)