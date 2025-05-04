# Add an executable for the bit problem
add_executable(bit main.cpp)

# Link the algorithms library
target_link_libraries(bit PRIVATE algorithms)
