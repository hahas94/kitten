# Add an executable for the aspenavenue problem
add_executable(aspenavenue main.cpp)

# Link the algorithms library
target_link_libraries(aspenavenue PRIVATE algorithms)
