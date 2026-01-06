# Add an executable for the cropeasy problem
add_executable(cropeasy main.cpp)

# Link the algorithms library
target_link_libraries(cropeasy PRIVATE algorithms)
