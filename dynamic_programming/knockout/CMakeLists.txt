# Add an executable for the knockout problem
add_executable(knockout main.cpp)

# Link the algorithms library
target_link_libraries(knockout PRIVATE algorithms)
