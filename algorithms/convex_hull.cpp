/**
 * convex_hull.cpp
 * ------------------
 * Description:
 *   Implementation file containing definitions for the Convex hull-finding
 *   algorithm Graham scan.
 *
 *   This algorithm builds a polygon that covers all the provided points while
 *   minimizing the circumference.
 *
 *   It starts by picking the bottom-left-most point, then sort all points
 *   according to the angle they make with this point. The hull then contains
 *   those points that keep making a left-turn when added to the list of
 *   already found polygon points, i.e. completes the polygon while keeping
 *   it convex.
 *   Given a line and a point, how do we determine whether the point makes
 *   a cw or ccw turn with respect to the line. From vector product we know
 *   that the resulting vector has a magnitude equal to the parallelogram
 *   formed by the two vectors, and the sign of that area determines how the
 *   two vectors are positioned. VxW results in a positive area when W is left
 *   of V, else it is negative. Thus we need to fins the sign of this area.
 *   The two vectors in question are V=P1->P2 and W=P1->P3.
 *
 *   The time complexity of this algorithm is O(n*log(n)), n being the number
 *   of points, where the sorting step is the most heavy.
 *
 * */

#include "convex_hull.hpp"

/**
 * Given a set of points, scan them to find the convex hull using
 * the Graham scan algorithm.
 *
 * @param points: A vector of points with (x, y) coordinates.
 * @return: A vector of the original points that constitute the hull.
 */
points_t scan(const points_t& points) {
    // Find the point with the lowest y-value.
    const auto it = std::ranges::min_element(points,
        [](const Point p1, const Point p2) {
            return true ? (p1.y < p2.y || (p1.y == p2.y && p1.x <= p2.x)) : false;
        });
    const Point lowest_point {*it};

    // Function to find the angle (-pi to pi) between a point
    // `p` and the lowest point.
    auto find_angle = [&lowest_point](const Point p) -> double {
        return {std::atan2(p.y - lowest_point.y, p.x - lowest_point.x)};
    };

    // Sorting the points based on their angles with the lowest point.
    points_t sorted_points = points;
    std::ranges::sort(sorted_points,
        [&lowest_point, find_angle](const Point p1, const Point p2) {
            const double theta1 = find_angle(p1), theta2 = find_angle(p2);
            const double d1 = std::hypot(p1.x - lowest_point.x, p1.y - lowest_point.y);
            const double d2 = std::hypot(p2.x - lowest_point.x, p2.y - lowest_point.y);
            return true ? (theta1 < theta2 || (theta1 == theta2 && d1 < d2))
                : false;
    });

    // S stack for holding the hull points during creation.
    std::deque<Point> hull;
    hull.push_front(sorted_points[0]);
    hull.push_front(sorted_points[1]);

    // Determine whether a third point p3 makes a counter-clockwise turn in
    // relation to the line passing through the points p1 and p2.
    // Using the cross-product between the vectors (p1p2) and (p1p3), we can
    // determine the turn based on the area formed by the parallelogram.
    // A left turn has a positive area while a right turn has a negative area.
    auto is_ccw = [](const Point p1, const Point p2, const Point p3) -> bool {
        const double area = (p2.x - p1.x) * (p3.y - p1.y) -
                            (p3.x - p1.x) * (p2.y - p1.y);
        return area >= 0;
    };

    // Scan through the points to find those points that keep making
    // a counter-clockwise turn starting from the lowest point.
    for (std::size_t i {2}; i < sorted_points.size(); i++) {
        const Point p3 = sorted_points[i];
        Point p2 = hull.front();
        hull.pop_front();
        while (!hull.empty() && !is_ccw(hull.front(), p2, p3)) {
            p2 = hull.front();
            hull.pop_front();
        }
        hull.push_front(p2);
        hull.push_front(p3);
    }

    points_t hull_points {hull.begin(), hull.end()};
    std::ranges::reverse(hull_points.begin(), hull_points.end());
    return hull_points;
}

// ============== END OF FILE ==============

