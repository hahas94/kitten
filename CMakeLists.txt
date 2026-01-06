# CMake version and project name
cmake_minimum_required(VERSION 3.25)
project(AlgorithmicProblemSolving VERSION 1.0 LANGUAGES CXX)

# Modern C++ standard settings
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # Disable compiler-specific extensions (e.g., GNU extensions)

# Global warnings/errors (applies to all targets)
add_compile_options(
    -Wall -Wextra -Wpedantic -Werror -Wfatal-errors
    -Weffc++ -Wold-style-cast
)

# Debug-specific flags (sanitizers, debug symbols, no optimizations)
set(CMAKE_CXX_FLAGS_DEBUG 
    "-g -O0 -D_GLIBCXX_DEBUG -fno-optimize-sibling-calls"
)

# Release-specific flags (aggressive optimizations, no debug overhead)
set(CMAKE_CXX_FLAGS_RELEASE 
    "-O3 -DNDEBUG"
)

# Enable testing
enable_testing()

# Include subdirectories
add_subdirectory(tests)
add_subdirectory(algorithms)
add_subdirectory(dynamic_programming)
add_subdirectory(greedy)
add_subdirectory(miscellaneous)
add_subdirectory(data_structures)
add_subdirectory(geometry)
