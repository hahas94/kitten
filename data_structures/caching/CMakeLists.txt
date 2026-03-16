# Add an executable for the caching problem
add_executable(caching main.cpp)

# Link the algorithms library
target_link_libraries(caching PRIVATE algorithms)
