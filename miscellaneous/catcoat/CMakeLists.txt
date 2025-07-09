# Add an executable for the catcoat problem
add_executable(catcoat main.cpp)

# Link the algorithms library
target_link_libraries(catcoat PRIVATE algorithms)
