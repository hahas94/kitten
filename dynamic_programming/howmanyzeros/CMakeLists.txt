# Add an executable for the howmanyzeros problem
add_executable(howmanyzeros main.cpp)

# Link the algorithms library
target_link_libraries(howmanyzeros PRIVATE algorithms)
