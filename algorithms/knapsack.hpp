/**
 * knapsack.hpp
 * ------------------
 * Description:
 *   Header file containing declarations for the Knapsack problem. 
 * */

#ifndef KNAPSACK_HPP
#define KNAPSACK_HPP
 
#include <iostream>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <utility>
#include <vector>

// Each item to be packed has a value and weight, hence a pair (value, weight).
// A list of items is a vector of such pairs.
using item_t = std::pair<int, int>;
using items_t = std::vector<item_t>;
std::vector<int> knapsack(const int capacity, const items_t& items);

#endif // KNAPSACK_HPP

// ============== END OF FILE ==============