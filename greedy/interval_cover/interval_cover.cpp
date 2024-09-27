#include "interval_cover.hpp"

/**
 * @brief Find a cover for an interval [A, B].
 * 
 * @param interval: Target interval [A, B, pos] to be covered.
 * @param intervals: A vector of interval objects.
 * @return vector of intervals used to cover target.
 */
intervals_t cover(const interval_t& interval, intervals_t& intervals) {
  intervals_t solution_intervals (intervals.size());
  intervals_t empty_solution {};
  int n_solution_intervals {0};
  const auto [A, B, P] = interval;

  std::ranges::sort(intervals, [&A, &B](const interval_t& it1, const interval_t& it2) {
    const auto [a1, b1, pos1] = it1;
    const auto [a2, b2, pos2] = it2;

    return (a1 == a2) ? b1 > b2 : a1 < a2;
  });

  auto update_solution {[&n_solution_intervals, &solution_intervals](const interval_t& it){
    solution_intervals.at(n_solution_intervals) = it; 
    n_solution_intervals++;
  }};

  const std::size_t n_intervals {intervals.size()};
  if(n_intervals == 0){return empty_solution;}
  double cA {A};
  double cB {A-1};
  double a, b;
  int pos;
  unsigned int i {0};
  interval_t it;
  interval_t dummy {-1, -1, -1};
  interval_t candidate {dummy};

  while(cB < B && i < n_intervals){
    it = intervals.at(i);
    std::tie(a, b, pos) = it;

    if(a <= cA){if(cB < b){cB = b; candidate = it;}}

    else if(i == 0){break;}  // gap in beginning

    else{
      cA = cB;
      update_solution(candidate);
      candidate = dummy;
      if(a <= cA){cB = b; candidate = it;}
      else{break;} // gap in middle
    }

    i++;
  }

  if(candidate != dummy){update_solution(candidate);}  // last interval

  if(n_solution_intervals > 0 && B <= cB){
    solution_intervals.resize(n_solution_intervals);
    std::ranges::reverse(solution_intervals);
    return solution_intervals;
  }

  return empty_solution;
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
