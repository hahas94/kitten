#!/bin/bash

# Usage: ./template.sh file_name problem_name kattis_problem_name


file_name=$1  # used in file names
problem_name=$2  # Used in normal text
kattis_problem_name=$3


# Create C++ file with boilerplate code
header_file="$file_name.hpp"
implementation_file="$file_name.cpp"
main_file="main.cpp"

# Insert template code into the implementation file.
touch $implementation_file
cat <<EOT >> $implementation_file
/**
 * $implementation_file
 * ------------------
 * Description:
 *   Implementation file containing definitions for the $problem_name problem. 
 * */

#include "$header_file"

void solve(){
    std::cout << "Solution code..." << std::endl;
}

// ============== END OF FILE ==============

EOT

# Insert template code into the main file.
touch $main_file
cat <<EOT >> $main_file
/**
* main.cpp
 * -----------------
 * $problem_name (https://open.kattis.com/problems/$kattis_problem_name):
 *   
 *
 * Solution:
 *   
 *
 **/
 
#include "$header_file"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    return 0;
}

// ============== END OF FILE ==============

EOT

# Insert template code into the header file.
touch $header_file
cat <<EOT >> $header_file
/**
 * $header_file
 * ------------------
 * Description:
 *   Header file containing declarations for the $problem_name problem. 
 * */
 
#include <iostream>

// ============== END OF FILE ==============

EOT

# Create input and output files
touch sample.in
touch sample.out

echo "Created template files. Done!"
