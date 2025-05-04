# Add an executable for the help problem
add_executable(help2 main.cpp)

# Link the algorithms library
target_link_libraries(help2 PRIVATE algorithms)
