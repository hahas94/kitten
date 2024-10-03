/**
* main.cpp
 * -----------------
 * Knapsack (https://open.kattis.com/problems/knapsack):
 *   Standard 0/1 Knapsack problem.
 *   
 *
 * Solution:
 *   Use of dynamic programming to find which items to pack.
 *   
 *
 **/
 
#include "../../algorithms/knapsack.hpp"

/**
 * @brief Read input, solve the problem, print out the solution.
 * 
 */
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int C, n, v, w;

  while(std::cin >> C >> n){
    items_t items (n);
    std::vector<int> is_packed (n);
    int n_packed {0};

    for(int i = 0; i < n; i++){
      std::cin >> v >> w;
      items.at(i) = std::pair(v, w);
    }
    is_packed = knapsack(C, items);
    n_packed = std::accumulate(is_packed.begin(), is_packed.end(), 0);
    std::cout << n_packed << "\n";
    for(int i = 0; i < n; i++){if(is_packed.at(i) == 1){std::cout << i << " ";}}
    std::cout << "\n";
  }
  std::cout << std::flush;

  return 0;
}

// ============== END OF FILE ==============

