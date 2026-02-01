/**
* main.cpp
 * -----------------
 * Points in polygon (https://open.kattis.com/problems/pointinpolygon):
 *   Given the vertices of simple polygon, determine whether another set of
 *   points lie inside, outside or on an edge of the polygon.
 *
 * Solution:
 *  The problem is solved using the ray-casting algorithm
 **/
 
#include <sstream>
#include "../../algorithms/ray_casting.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n_polygon_points, n_test_points;
    std::ostringstream oss {};
    std::string line;
    Point P {};

    while (true) {
        std::cin >> n_polygon_points;
        if (n_polygon_points == 0) {break;}

        points_t polygon (n_polygon_points);
        for (int i = 0; i < n_polygon_points; i++) {
            std::cin >> polygon[i].x >> polygon[i].y;
        }

        std::cin >> n_test_points;
        points_t test_points (n_test_points);
        for (int i = 0; i < n_test_points; i++) {
            std::cin >> P.x >> P.y;
            const int output {in_polygon(P, polygon)};
            std::string result = output == -1 ? "out" : output == 0 ? "on" : "in";
            oss << result << "\n";
        }
    }
    std::cout << oss.str();
    return 0;
}

// ============== END OF FILE ==============

