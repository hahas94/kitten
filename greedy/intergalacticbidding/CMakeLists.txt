# Add an executable for the intergalacticbidding problem
add_executable(intergalacticbidding main.cpp)

# Link the algorithms library
target_link_libraries(intergalacticbidding PRIVATE algorithms)
