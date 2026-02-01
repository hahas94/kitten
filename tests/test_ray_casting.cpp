#include <catch2/catch_test_macros.hpp>
#include "ray_casting.hpp"

TEST_CASE("Ray casting: Example 1") {
    points_t points = {{1, 4}, {8, 4}, {5, 0}, {9, -5}, {1, -5}, {4, 0}};
    points_t test_points {{1, 1}, {4, 3}, {8, -2}, {9, -5}};
    std::vector<int> ans {-1, 1, -1, 0};

    for (std::size_t i {0}; i < ans.size(); i++) {
        int output {in_polygon(test_points[i], points)};
        REQUIRE (ans[i] == output);
    }
}

TEST_CASE("Ray casting: Example 2") {
    points_t points = {{-2, 5}, {7, 5}, {7, -2}, {11, -2}, {11, -4},
                       {4, -4}, {4, 3}, {-2, 3}};
    points_t test_points {{2, 1}, {4, 5}, {2, -4}, {10, -3}, {-3, 5},
                          {-2, 4}, {-3, 3}, {8, 5}, {8, -2}};
    std::vector<int> ans {-1, 0, -1, 1, -1, 0, -1, -1, 0};

    for (std::size_t i {0}; i < ans.size(); i++) {
        int output {in_polygon(test_points[i], points)};
        REQUIRE (ans[i] == output);
    }
}
