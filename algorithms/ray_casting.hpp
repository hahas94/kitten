/**
 * ray_casting.hpp
 * ------------------
 * Description:
 *   Header file containing declarations for the ray-casting algorithm.
 * */

#ifndef RAY_CASTING_HPP
#define RAY_CASTING_HPP
 
#include <iostream>
#include <string>
#include <vector>

struct Point {
    double x, y;
};

using points_t = std::vector<Point>;

int in_polygon(const Point& point, const points_t& points);

#endif

// ============== END OF FILE ==============

