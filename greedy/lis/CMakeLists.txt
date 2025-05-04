# Add an executable for the lis problem
add_executable(lis main.cpp)

# Link the algorithms library
target_link_libraries(lis PRIVATE algorithms)
