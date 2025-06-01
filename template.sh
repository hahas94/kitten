#!/bin/bash

# Use this file for generating template code for solving a problem.
# Each new problem will be within its directory, and this directory 
# will itself belong to a problem category. Thus pass both problem name
# and name of problem category directory. 
# Sample input and output files are created as well, and relevant cmake
# files will be updated.

# Run from root of project.
# Usage: ./template.sh dir_name problem_name

dir_name=$1
problem_name=$2

# Check if the problem category directory exists
if [ ! -d "$dir_name" ]; then
    # If it doesn't exist, create it
    mkdir -p "$dir_name"
    # create a cmake file within it
    touch "$dir_name/CMakeLists.txt"
    echo "add_subdirectory(dir_name)" >> "CMakeLists.txt"
fi

echo "add_subdirectory($problem_name)" >> "$dir_name/CMakeLists.txt"

mkdir -p "$dir_name/$problem_name"
touch "$dir_name/$problem_name/CMakeLists.txt"
cat <<EOT >> $dir_name/$problem_name/CMakeLists.txt
# Add an executable for the $problem_name problem
add_executable($problem_name main.cpp)

# Link the algorithms library
target_link_libraries($problem_name PRIVATE algorithms)
EOT

touch "$dir_name/$problem_name/main.cpp"
touch "$dir_name/$problem_name/sample.in"
touch "$dir_name/$problem_name/sample.output"

cat <<EOT >> $dir_name/$problem_name/main.cpp
/**
* main.cpp
 * -----------------
 * $problem_name (https://open.kattis.com/problems/$problem_name):
 *   
 *
 * Solution:
 *   
 *
 **/
 
//#include "../../algorithms/$dir_name.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    return 0;
}

// ============== END OF FILE ==============

EOT

echo "Created template files."
