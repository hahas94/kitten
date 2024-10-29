/**
* main.cpp
 * -------
 * Longest Increasing Subsequence (https://open.kattis.com/problems/longincsubseq):
 *  Given a sequence of integers, find the longest subsequence that is increasing.
 *
 * Solution:
 *  Using the Patience algorithm, we put each number into a pile, where a new pile is
 *  added when the number is larger than all numbers at the end of the piles. If the 
 *  number is not larger than all numbers on the end of the piles, then it will be placed
 *  at the left most pile such that the last element on it is not less than the current 
 *  element. Also, each time an element is added to a pile, it stores a pointer the the 
 *  end element of the previous pile. 
 *  One all elements are in their respective piles, we can find the solution by starting
 *  from the last element of the last pile, and following the pointers. This will result
 *  in a subsequence of length equal to number of piles, and increasing.
 * 
 *  The algorithm runs in O(n * log(n)).
 *   
 *
 **/
 
#include "../../algorithms/lis.hpp"

void print_solution(const std::vector<int>& sequence);

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;

    while(std::cin >> n){
        std::vector<int> sequence (n);
        for(int i = 0; i < n; i++){
            std::cin >> sequence[i];
        }
        std::vector<int> solution {lis(sequence)};
        print_solution(solution);
    }
    
    std::cout << std::flush;
    return 0;
}

/**
 * @brief Print the solution of a test case.
 * 
 * @param sequence: binary vector, where a 1 indicates that the index is part of the subsequence. 
 */
void print_solution(const std::vector<int>& sequence){
    std::size_t length {sequence.size()};
    std::cout << length << "\n";
    for(const int& el: sequence){
        std::cout << el << " ";
    }
    std::cout << "\n";
}

// ============== END OF FILE ==============

