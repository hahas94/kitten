# Add an executable for the knapsack problem
add_executable(knapsack main.cpp)

# Link the algorithms library
target_link_libraries(knapsack PRIVATE algorithms -fsanitize=undefined -fsanitize=address)
