/**
* main.cpp
 * -----------------
 * Crop Triangles (Easy) (https://open.kattis.com/problems/cropeasy):
 *  Given a set of vertices in a grid, calculate the number of triangles
 *  that can be made out of these vertices such that the center of the
 *  triangle is a point on the grid. For a triangle with vertices
 *  {(x1, y1), (x2, y2), (x3, y3)}, the center is defined as:
 *  (1/3)*(x1+x2+x3, y1+y2+y3).
 *
 * Solution:
 *  Since the number of trees in the problem is at most 100, we can simply
 *  find the solutions using brute force, by comparing every pair of points
 *  with a third point.
 *  The time complexity is O(n^3), `n` being number of trees.
 *
 **/

#include <iostream>
#include <vector>

using ull_t = unsigned long long;

struct Point {
    ull_t x;
    ull_t y;
};

int count_triangles(int n, int A, int B, int C, int D, ull_t x, ull_t y, int M);


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int T, n, A, B, C, D, M;
    ull_t x, y;
    std::cin >> T;
    for (int i {1}; i <= T; i++) {
        std::cin >> n >> A >> B >> C >> D >> x >> y >> M;
        const int n_triangles {count_triangles(n, A, B, C, D, x, y, M)};
        std::cout << "Case #" << i << ": " << n_triangles << "\n";
    }
    return 0;
}

/**
 * Given number of trees, parameters for generating points and
 * the first point, compute the number of trees with a valid center.
 */
int count_triangles(const int n, const int A, const int B, const int C,
                    const int D, ull_t x, ull_t y, const int M) {
    int n_triangles {0};
    std::vector<Point> points (n);

    for (int i {0}; i < n; i++) {
        points[i] = {x, y};
        x = (A*x + B) % M;
        y = (C*y + D) % M;
    }

    Point p1, p2, p3;
    ull_t xc, yc;
    for (int i {0}; i < n - 2; i++) {
        for (int j {i + 1}; j < n - 1; j++) {
            for (int k {j + 1}; k < n; k++) {
                p1 = points[i], p2 = points[j], p3 = points[k];
                xc = p1.x + p2.x + p3.x;
                yc = p1.y + p2.y + p3.y;
                if (xc % 3 == 0 && yc % 3 == 0) {n_triangles++;}
            }
        }
    }

    return n_triangles;
}

// ============== END OF FILE ==============
