# CMake version and project name
cmake_minimum_required(VERSION 3.25)
project(AlgorithmicProblemSolving  VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add global compile options for all targets
add_compile_options(-Wall -Wextra -Werror -Wfatal-errors -Wpedantic
                    -Weffc++ -Wold-style-cast
                    -D_GLIBCXX_DEBUG -fmax-errors=1 
                    -fsanitize=undefined -fsanitize=address)


enable_testing()

# include tests folder
add_subdirectory(tests)

# Add the algorithms folder as a library
add_subdirectory(algorithms)

# Add each problem category folder
add_subdirectory(dynamic_programming)
add_subdirectory(greedy)
add_subdirectory(miscellaneous)
