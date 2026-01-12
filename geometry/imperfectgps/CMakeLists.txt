# Add an executable for the imperfectgps problem
add_executable(imperfectgps main.cpp)

# Link the algorithms library
target_link_libraries(imperfectgps PRIVATE algorithms)
