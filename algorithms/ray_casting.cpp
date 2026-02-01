/**
 * ray_casting.cpp
 * ------------------
 * Description:
 *   Implementation file containing definitions for the ray-casting problem.
 *
 *   Given a simple polygon and a point (xp, yp), this algorithm determines
 *   whether the point lies inside, outside or on an edge of the polygon.
 *   The idea is to cast a ray from the point to the right and count
 *   the number of times the ray intersects with an edge of the polygon.
 *   If the number of intersections is even, then the point is outside while
 *   it is inside if the number is odd.
 *
 *   To check whether the point lies on
 *   an edge, the point is on the edge if it is collinear with the edge and
 *   its x, y values are within the line-segment.
 *
 *   The point is checked for intersection with each of the edges. To find
 *   whether the ray crosses the line-segment, we need to find the x-coordinate
 *   of the intersection point (xi, yi). We know that since the ray is
 *   straight, the y-coordinate yi will be identical to the point's
 *   y-coordinate yp.
 *   The equation of the line segment for this intersection point is then:
 *    yp = a*xi + b, where
 *    a = dy/dx = y2-y1/x2-x1 and
 *    b = y1 - a*x1 (using any of the edge's points)
 *    xi = (yp - b) / a = (yp - (y1 - a*x1)) / a
 *       = (yp - y1) * (x2-x1/y2-y1) + x1
 *
 *   If xp < xi, then the ray will intersect with the line-segment, meaning
 *   it is to the left of the line segment.
 *
 *   Also, we first need to check that yp is not below or above both points
 *   y-coordinates.
 *
 *   The time complexity of this algorithm is O(n), n being the polygon's
 *   number of vertices.
 * */

#include "ray_casting.hpp"

/**
 * Return whether point inside, outside or on polygon edge.
 * @param point: An arbitrary point.
 * @param points: The vertices of a simple polygon.
 * @return -1 (outside), 0 (on an edge), 1 (inside).
 */
int in_polygon(const Point& point, const points_t& points) {
    int output = -1;
    int intersection_counter = 0;

    for (std::size_t i = 0; i < points.size(); i++) {
        const Point P {points[i]}, Q {points[(i+1)%points.size()]};
        const double min_x {std::min(P.x, Q.x)},
                     min_y {std::min(P.y, Q.y)},
                     max_x {std::max(P.x, Q.x)},
                     max_y {std::max(P.y, Q.y)};

        // Vectors v, w, and the cross-product parallelogram area between them.
        const Point v {Q.x - P.x, Q.y - P.y}, w {point.x - P.x, point.y - P.y};
        const double area = v.x * w.y - v.y * w.x;

        // Checking whether point is on the segment, i.e. collinear and between.
        if (area == 0 &&
           (min_y <= point.y && point.y <= max_y) &&
           (min_x <= point.x && point.x <= max_x)) {
            output = 0; break;
        }

        if (((point.y < min_y) != (point.y < max_y)) && !(point.x > max_x)) {
            const double slope = (Q.y - P.y) / (Q.x - P.x);
            const double x_intersection {((point.y - P.y) / slope) + P.x};
            if (point.x < x_intersection) {intersection_counter++;}
        }
    }
    return (output == 0) ? 0 : (intersection_counter % 2 == 0) ? -1 : 1;
}

// ============== END OF FILE ==============

