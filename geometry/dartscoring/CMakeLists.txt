# Add an executable for the dartscoring problem
add_executable(dartscoring main.cpp)

# Link the algorithms library
target_link_libraries(dartscoring PRIVATE algorithms)
