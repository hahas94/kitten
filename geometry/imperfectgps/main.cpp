/**
* main.cpp
 * -------
 * Imperfect GPS (https://open.kattis.com/problems/imperfectgps):
 *  Given a set of recorded points on a path and the times of reaching them,
 *  as well as a method for estimating points on that path using a gps,
 *  calculate the error of the actual distance that is missed by the gps.
 *
 * Solution:
 *  We can generate all points on the path for each second, simply by tracking
 *  the lines between each two consecutive points. From these points we can
 *  find the distance run according to the gps records, by selecting certain
 *  points along the actual path.
 *
 **/

#include <iomanip>
#include <iostream>
#include <math.h>
#include <unordered_map>
#include <vector>

struct Point {
    double x, y;
    int t;
};

using points_t = std::vector<Point>;

double calc_dist(const Point& p1, const Point& p2);
double estimate_error(const points_t& points, int interval);

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n_points, interval;
    std::cin >> n_points >> interval;
    points_t points (n_points);
    for (int i = 0; i < n_points; i++) {
        std::cin >> points[i].x >> points[i].y >> points[i].t;
    }
    std::cout << std::fixed << estimate_error(points, interval)
              << std::setprecision(6) << std::endl;
    return 0;
}

/**
 * Calculate the Euclidean distance between two points.
 * @param p1: First point
 * @param p2: Second point
 * @return: Euclidean distance.
 */
double calc_dist(const Point& p1, const Point& p2) {
    const double dist = std::sqrt(std::pow((p1.x - p2.x), 2) +
                                  std::pow((p1.y - p2.y), 2));
    return dist;
}

/**
 * Estimate the error between a gps tracked path and the actual path.
 * @param points: Recorded points on an actual path.
 * @param interval: The time interval a gps records positions.
 * @return: The percentage of the actual distance run that is missed by the gps.
 */
double estimate_error(const points_t& points, const int interval) {
    double actual_dist {0}, estimated_dist {0};
    const int endtime {points.back().t};
    std::unordered_map<int, Point> runner_path;

    for (std::size_t i {0}; i < points.size() - 1; i++) {
        const Point p1 {points[i]}, p2 {points[i+1]};
        const double dist {calc_dist(p1, p2)};
        const double dx {p2.x - p1.x}, dy {p2.y - p1.y};
        const int duration {p2.t - p1.t};
        const double vx {dx / duration}, vy {dy / duration};
        int t {0};
        while (t <= duration) {
            runner_path[t + p1.t] = {p1.x + (t * vx), p1.y + (t * vy), 0};
            t++;
        }
        actual_dist += dist;
    }

    int gps_time {0};
    while (gps_time <= endtime) {
        if (gps_time + interval > endtime) {
            estimated_dist += calc_dist(runner_path[gps_time], points.back());
            break;
        }
        estimated_dist += calc_dist(runner_path[gps_time],
                                    runner_path[gps_time + interval]);
        gps_time += interval;
    }

    return 100 * std::abs(estimated_dist - actual_dist) / actual_dist;
}

// ============== END OF FILE ==============

