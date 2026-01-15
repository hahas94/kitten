/**
 * convex_hull.hpp
 * ------------------
 * Description:
 *   Header file containing declarations for the Convex-hull finding algorithm
 *   Graham scan.
 * */

#ifndef CONVEX_HULL_HPP
#define CONVEX_HULL_HPP

#include <algorithm>
#include <iostream>
#include <deque>
#include <math.h>
#include <vector>

struct Point {
    double x, y;
};

using points_t = std::vector<Point>;

points_t scan(const points_t& points);
#endif

// ============== END OF FILE ==============

