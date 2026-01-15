#include <catch2/catch_test_macros.hpp>
#include "convex_hull.hpp"

TEST_CASE("Convex hull: Example 1") {
    points_t points = {{1, 2}, {2, 3}, {5, 3}, {3, 2}, {2, 0}, {6, 2}};
    points_t hull = scan(points);
    points_t ans {{2, 0}, {6, 2}, {5, 3}, {2, 3}, {1, 2}};

    REQUIRE (hull.size() == ans.size());
    for (std::size_t i {0}; i < hull.size(); i++) {
        REQUIRE (hull[i].x == ans[i].x);
        REQUIRE (hull[i].y == ans[i].y);
    }
}

TEST_CASE("Convex hull: Example 2") {
    points_t points = {{2, 0}, {5, 1}, {5, 4}, {2, 2}, {8, 3},
                       {6, 2}, {4, 6}, {1, 3}};
    points_t hull = scan(points);
    points_t ans {{2, 0}, {5, 1}, {8, 3}, {4, 6}, {1, 3}};

    REQUIRE (hull.size() == ans.size());
    for (std::size_t i {0}; i < hull.size(); i++) {
        REQUIRE (hull[i].x == ans[i].x);
        REQUIRE (hull[i].y == ans[i].y);
    }
}

TEST_CASE("Convex hull: Example 3") {
    points_t points = {{0, 0}, {5, 0}, {0, 2.3}, {-4, 1.2}, {1, -6}, {0.5, 5.1}};
    points_t hull = scan(points);
    points_t ans {{1, -6}, {5, 0}, {0.5, 5.1}, {-4, 1.2}};

    REQUIRE (hull.size() == ans.size());
    for (std::size_t i {0}; i < hull.size(); i++) {
        REQUIRE (hull[i].x == ans[i].x);
        REQUIRE (hull[i].y == ans[i].y);
    }
}

TEST_CASE("Convex hull: Example 4") {
    points_t points = {{2, 2}, {2, 0}, {3, 1}, {1, 0}, {0, 0}};
    points_t hull = scan(points);
    points_t ans {{0, 0}, {1, 0}, {2, 0}, {3, 1}, {2, 2}};
    REQUIRE (hull.size() == ans.size());
    for (std::size_t i {0}; i < hull.size(); i++) {
        REQUIRE (hull[i].x == ans[i].x);
        REQUIRE (hull[i].y == ans[i].y);
    }
}
