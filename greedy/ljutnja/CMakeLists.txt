# Add an executable for the ljutnja problem
add_executable(ljutnja main.cpp)

# Link the algorithms library
target_link_libraries(ljutnja PRIVATE algorithms)
