# Add an executable for the Interval Cover problem
add_executable(interval_cover main.cpp)

# Link the algorithms library
target_link_libraries(interval_cover PRIVATE algorithms)