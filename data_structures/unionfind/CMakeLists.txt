# Add an executable for the unionfind problem
add_executable(unionfind main.cpp)

# Link the algorithms library
target_link_libraries(unionfind PRIVATE algorithms)
