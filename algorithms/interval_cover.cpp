/**
* interval_cover.cpp
 * -----------------
 * Description:
 *   Implementation file containing definitions for the Interval Cover problem. 
 * 
 *   Given a target interval [A, B] and a list of intervals 
 *   {[a1, b1],..., [an, bn]}, pick the minimum possible subset of 
 *   these intervals to cover the target interval, or state not 
 *   possible if so.
 *   Example problem in real life: Ensuring there are always some worker
 *   for a task during a time period, while avoiding to schedule workers
 *   unneccesarily.
 *
 * Solution:
 *   Sort the intervals based on smallest starting time and longest ending 
 *   time. For instance:
 *     ..........
 *     ......
 *       ........
 *         ...
 *              ...
 *   The idea is then to select an interval the covers the left-most uncovered
 *   point, while it is the longest among such intervals. This is done until all
 *   points are covered. If at any point there is a gap, then no solution can exist.
 * 
 *   The time complexity of this solution is O(n*log(n)) for sorting, and O(n) for the
 *   intervals selection.
 * 
 **/

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

// ============== END OF FILE ==============
