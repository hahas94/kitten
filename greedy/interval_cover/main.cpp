/**
* main.cpp
 * -----------------
 * Interval Cover (https://open.kattis.com/problems/intervalcover):
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
 *   
 * 
 *  
 *
 **/

#include "interval_cover.hpp"

int main() {
  solve();
  std::cout << std::flush;
  return 0;
}

// ============== END OF FILE ==============