# Create a static library from the algorithms
add_library(algorithms STATIC knapsack.cpp interval_cover.cpp lis.cpp unionfind.cpp)

# Specify the include directory
target_include_directories(algorithms PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
