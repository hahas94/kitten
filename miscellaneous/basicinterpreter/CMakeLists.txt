# Add an executable for the basicinterpreter problem
add_executable(basicinterpreter main.cpp)

# Link the algorithms library
target_link_libraries(basicinterpreter PRIVATE algorithms)
