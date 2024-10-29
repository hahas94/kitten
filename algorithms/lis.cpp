/**
 * lis.cpp
 * -------
 * Description:
 *  Implementation file containing definitions for the Longest Increasing Subsequence problem. 
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
 * */

#include "lis.hpp"

/**
 * @brief Find and return the indices of the longest increasing subsequence 
 *        in a sequence of integers.
 * 
 * @param sequence: vector of integers 
 * @return std::vector<int>: indices of longest subsequence elements in sequence.
 */
std::vector<int> lis(const std::vector<int>& sequence){
    const std::size_t sequence_length {sequence.size()};
    std::vector<int> last_in_pile (sequence_length, std::numeric_limits<int>::max());
    std::vector<int> last_in_pile_index (sequence_length, -1);
    std::vector<int> pointers (sequence_length, -1);
    int num_piles {0};
    int pile_index {-1};

    for(std::size_t i {0}; i < sequence_length; i++){
        int element {sequence.at(i)};
        auto iter {std::ranges::lower_bound(last_in_pile, element)};
        pile_index = std::distance(last_in_pile.begin(), iter);

        last_in_pile.at(pile_index) = element;
        last_in_pile_index.at(pile_index) = i;

        if(pile_index == num_piles){num_piles++;}
        if(pile_index > 0){pointers.at(i) = last_in_pile_index.at(pile_index-1);}
    }

    std::vector<int> solution (num_piles);
    int index {last_in_pile_index.at(num_piles-1)};
    int i {num_piles-1};

    while(i >= 0){
        solution.at(i) = index;
        index = pointers.at(index);
        i--;
    }

    return solution;
}

// ============== END OF FILE ==============

