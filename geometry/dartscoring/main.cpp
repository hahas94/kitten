/**
* main.cpp
 * -----------------
 * Dart scoring (https://open.kattis.com/problems/dartscoring):
 *  Given the locations of a set of darts, i.e. points on a 2D map,
 *  wrap a string tightly around the outermost darts so that they are fully
 *  enclosed, and find the length of that string.
 *
 * Solution:
 *  This task requires to find the convex hull of the darts and compute its
 *  circumference.
 *
 **/

#include <iomanip>
#include <sstream>
#include <string>

#include "../../algorithms/convex_hull.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::ostringstream oss;

    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        points_t points;

        double x, y;
        while (iss >> x >> y) {
            points.push_back({x, y});
        }

        double dist {0};
        if (points.size() > 1) {
            points_t hull_points {scan(points)};
            hull_points.push_back(hull_points.front());

            for (size_t i {0}; i < hull_points.size() - 1; i++) {
                const Point p1 = hull_points[i], p2 = hull_points[i + 1];
                dist += std::hypot(p2.x - p1.x, p2.y - p1.y);
            }
        }

        double score {100 * points.size() / (1 + dist)};
        oss << std::fixed << score << std::setprecision(5) << "\n";
    }

    std::cout << oss.str();
    return 0;
}

// ============== END OF FILE ==============
