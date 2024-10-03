#!/bin/bash

# This file can be used for creating a submission file for a problem
# such that it can be submitted to Kattis. Since the solution to each
# problem includes files from different folders, we need to create single 
# files for submission. This approach combines all necessary pieces of code
# into one file called `submission.cpp`.

# Usage: ./create_submission.sh problem_folder algorithm_name1 algorithm_name2 ...

# Check if enough arguments are provided
if [ "$#" -lt 2 ]; then
    echo "Usage: ./create_submission.sh problem_folder algorithm_name1 algorithm_name2 ..."
    exit 1
fi

problem_folder="$1"
output_file="submission.cpp"
shift # Shift to get algorithm names as the remaining arguments

# Start with an empty output file
> "$output_file"

# Function to append a file's content to the output, filtering out #include statements
append_file_without_includes() {
    local file="$1"
    grep -v '#include' "$file" >> "$output_file"
    echo "" >> "$output_file"  # Add a newline after each file for clarity
}

# 1. Append the content of each algorithm's header file (*.hpp)
for algo in "$@"
do
    header_file="algorithms/${algo}.hpp"
    
    if [ -f "$header_file" ]; then
        echo "// Content from ${header_file}" >> "$output_file"
        cat "$header_file" >> "$output_file"
        echo "" >> "$output_file"
    else
        echo "Warning: Header file $header_file does not exist."
    fi
done

# 2. Append the content of the problem's main.cpp
problem_file="${problem_folder}/main.cpp"
if [ -f "$problem_file" ]; then
    echo "// Content from ${problem_file}" >> "$output_file"
    append_file_without_includes "$problem_file"
    echo "" >> "$output_file"
else
    echo "Error: Problem file $problem_file does not exist."
    exit 1
fi

# 3. Append the content of each algorithm's source file (*.cpp) without #include lines
for algo in "$@"
do
    source_file="algorithms/${algo}.cpp"
    
    if [ -f "$source_file" ]; then
        echo "// Content from ${source_file}" >> "$output_file"
        append_file_without_includes "$source_file"
    else
        echo "Warning: Source file $source_file does not exist."
    fi
done

echo "Submission file created: $output_file"

