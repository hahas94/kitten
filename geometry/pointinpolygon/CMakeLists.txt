# Add an executable for the point_in_polygon problem
add_executable(pointinpolygon main.cpp)

# Link the algorithms library
target_link_libraries(pointinpolygon PRIVATE algorithms)
