#!/bin/bash

# Use this file for generating template code for implementation of an algorithm.
# It will create two files, `algorithms/algo_name.cpp` and `algorithms/algo_name.hpp`,
# as well as updating the relevant cmake files.

# Run from root of project.
# Usage: ./algo_template.sh algo_name

file_name=$1  
filename_uppercase=$(echo "$file_name" | tr '[:lower:]' '[:upper:]')

header_file="$file_name.hpp"
src_file="$file_name.cpp"

# Insert template code into the header file.
touch "algorithms/$header_file"
cat <<EOT >> algorithms/$header_file
/**
 * $header_file
 * ------------------
 * Description:
 *   Header file containing declarations for the $file_name algorithm. 
 * */

#ifndef ${filename_uppercase}_HPP
#define ${filename_uppercase}_HPP
 
#include <iostream>

#endif

// ============== END OF FILE ==============

EOT

# Insert template code into the implementation file.
touch "algorithms/$src_file"
cat <<EOT >> algorithms/$src_file
/**
 * $src_file
 * ------------------
 * Description:
 *   Implementation file containing definitions for the $file_name problem. 
 * */

#include "$header_file"

void solve(){
    std::cout << "Solution code..." << std::endl;
}

// ============== END OF FILE ==============

EOT

sed -i '' 's/\(add_library(algorithms STATIC.*\))/\1 '"$src_file"')/' algorithms/CMakeLists.txt

echo "Created algorithm template files."