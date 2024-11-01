find_package(Catch2 REQUIRED)

add_executable(test_unionfind test_unionfind.cpp)
target_link_libraries(test_unionfind PRIVATE Catch2::Catch2WithMain algorithms  
                      -fsanitize=undefined -fsanitize=address)

include(CTest)
include(Catch)
catch_discover_tests(test_unionfind)