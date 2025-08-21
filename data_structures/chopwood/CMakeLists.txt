# Add an executable for the chopwood problem
add_executable(chopwood main.cpp)

# Link the algorithms library
target_link_libraries(chopwood PRIVATE algorithms)
