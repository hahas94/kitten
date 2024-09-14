/**
* main.cpp
 * -----------------
 * Conga Line (https://open.kattis.com/problems/congaline):
 *   Given an array of couples and a set of instructions, where the instructions
 * 	 may alter the position of any one person in the array to the end, or behind 
 *   their partner, the task is to perform all instructions and print the final 
 *   arrangement in the line as well as which people's names have been called.
 *
 * Solution:
 *   Due to the nature of the problem, lots of deletions and insertions may occurr
 *   in this problem, and lots of searching as well. The Linked List data structure
 *   can be used to handle the deletions and insertions in an efficient way.
 *   The searching part can be solved by using a mapping between each person and
 *   a pointer to it. This way, moving behind a partner can be done in constant 
 *   time.
 * 
 *  The code contains two important functions, `main_program()` that does the reading
 *  and printing, and the `solve_problem()` function that performs the instructions. 
 *
 **/

#include "conga_line.hpp"

int main() {
  // for fast reading
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);

  main_program();

  return 0;
}

// ============== END OF FILE ==============
