# Add an executable for the spiderman problem
add_executable(spiderman main.cpp)

# Link the algorithms library
target_link_libraries(spiderman PRIVATE algorithms -fsanitize=undefined -fsanitize=address)
