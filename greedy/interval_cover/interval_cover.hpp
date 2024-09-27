#ifndef INTERVAL_COVER_HPP
#define INTERVAL_COVER_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <algorithm> 
#include <iterator>
#include <vector>
#include <tuple>

// an interval [A, B] is represented with a tuple (A, B, position)
// where `position` is its index in the intervals list.
using interval_t = std::tuple<double, double, int>;
using intervals_t = std::vector<interval_t>;

intervals_t cover(const interval_t& interval, intervals_t& intervals);

void print_solution(intervals_t& intervals);

void solve();

#endif // INTERVAL_COVER_HPP