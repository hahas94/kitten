# Add an executable for the turbo problem
add_executable(turbo main.cpp)

# Link the algorithms library
target_link_libraries(turbo PRIVATE algorithms)
