/**
* main.cpp
 * -----------------
 * Interval Cover (https://open.kattis.com/problems/intervalcover):
 *   Given a target interval [A, B] and a list of intervals 
 *   {[a1, b1],..., [an, bn]}, pick the minimum possible subset of 
 *   these intervals to cover the target interval, or state not 
 *   possible if so.
 *
 * Solution:
 *   Use a greedy approach that will cover more and more of the target interval
 *   for each new subinterval chosen.
 * 
 **/

#include "../../algorithms/interval_cover.hpp"

void print_solution(intervals_t& intervals);
void solve();

int main() {
  solve();
  std::cout << std::flush;
  return 0;
}

/**
 * @brief Print the solution.
 * 
 * Number of intervals is printed at beginning. If list
 * is empty, then no solution is found, thus print `impossible`.
 * 
 * @param intervals: A vector of interval objects [A, B, pos].
 */
void print_solution(intervals_t& intervals) {
  if(intervals.size() > 0){
    std::cout << intervals.size() << "\n";
    
    std::ranges::transform(intervals, 
      std::ostream_iterator<int>(std::cout, " "), 
      [](const interval_t& tup){return std::get<2> (tup);}
    );
  }
  else{
    std::cout << "impossible";
  }
  std::cout << "\n";
}

/**
 * @brief Run solution on input instances.
 * 
 * Read the input instances, build vector of intervals and
 * solve the problem. Finally print the solution.
 * 
 */
void solve() {
  // Read input until EOF is reached
  double A, B;
  double a, b;
  int n_intervals;
  intervals_t solution;

  while (std::cin >> A >> B) {
      std::cin >> n_intervals;
      intervals_t intervals (n_intervals);
      
      for(int i = 0; i < n_intervals; i++){
        std::cin >> a >> b;
        if((a <= A && A <= b) || (a <= B && B <= b) || (A <= a && b <= B)){
          intervals.at(i) = {std::max(a, A), std::min(b, B), i};
        }
      }    
      
      solution = cover({A, B, -1}, intervals);
      print_solution(solution);
  }
}

// ============== END OF FILE ==============
