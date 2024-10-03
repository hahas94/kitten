/**
 * knapsack.cpp
 * ------------
 * Description:
 *   Implementation file containing definitions for the Knapsack problem. 
 * 
 *   Given a bag of a max capacity, and a number of items each with a weight
 *   and profit, the problem is to determine which items to put in the bag
 *   such that their combined profit is maximal while respecting the maximum
 *   capacity constraint.
 * 
 * Solution:
 *   This problem can be solved recursively, where for each item a decision is
 *   made, namely whether to include it in the bag or exclude it.
 *   If including it, then we need to decrease the bag capacity and then solve 
 *   for the remaining items, otherwise this item is excluded and the solution
 *   continues with remaining items. Out of these two choices, whichever results
 *   in higher profit is selected. Thus the recursive formula is:
 *     
 *     profit(capacity, items[1..n]) = max{profit(capacity, items[1..n-1]), 
 *                                         profit(capacity-Wn, items[1..n-1]) + Pn
 *                                        }
 *     where Wn and Pn are the weight and profit of item n.
 * 
 *   In the actual implementation, instead of using the recursive formula, a table
 *   is used to track the value for all different combinations of weights and items.
 *   The time complexity is thus O(C*n), where C is the bag capacity and n is the number
 *   of items.
 * */

#include "knapsack.hpp"

/**
 * @brief Find which items to pack in a knapsack.
 * 
 * @param capacity: knapsack maximum capacity
 * @param items: pairs of {value, weight} tuples 
 * @return std::vector<int>: binary vector denoting whether an item is packed. 
 */
std::vector<int> knapsack(const int capacity, const items_t& items){
  std::size_t n_items {items.size()};
  std::vector<std::vector<int>> values_table (n_items+1, std::vector<int> (capacity+1, 0));
  std::vector<int> is_packed (n_items);
  int max_value {0};
  int max_row {0}, max_col {0};

  // filling the values for each number of items and capacity combination.
  for(std::size_t i = 1; i <= n_items; i++){
    auto [value, weight] = items.at(i-1);
    for(int c = 1; c <= capacity; c++){
      int include_value {c - weight < 0 ? 0 : values_table.at(i-1).at(c-weight) + value};
      int exclude_value {values_table.at(i-1).at(c)};
      values_table.at(i).at(c) = std::max(include_value, exclude_value);
      if(values_table.at(i).at(c) > max_value){
        max_value = values_table.at(i).at(c);
        max_row = i;
        max_col = c;
      }
    }
  }

  while(max_row > 0 && max_col > 0){
    auto [value, weight] = items.at(max_row-1);
    if(values_table.at(max_row-1).at(max_col) != values_table.at(max_row).at(max_col)){
      is_packed.at(max_row-1) = 1;
      max_col -= weight;
    }
    max_row--;
  }
  
  return is_packed;
}

// ============== END OF FILE ==============

