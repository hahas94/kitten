# Add an executable for the metube problem
add_executable(metube main.cpp)

# Link the algorithms library
target_link_libraries(metube PRIVATE algorithms)
