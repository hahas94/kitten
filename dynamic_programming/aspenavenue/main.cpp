/**
* main.cpp
 * -----------------
 * Aspen Avenue (https://open.kattis.com/problems/aspenavenue):
 *  Given a list of trees and a list of planting positions, determine which
 *  tree to move to which position such as to minimize the total distance 
 *  of trees moved, while satisfying a set of constraints. 
 *
 * Solution:
 *  The recursive version of this problem is as follows:
 *      if 0 trees are planted on the left side of the road and 0 trees
 *      planted on the righted side of the road, what is the minimal distance
 *      to plant the remaining trees?
 *      The answer is the minimum between {planting one tree on left, 
 *      planting one tree on right} and then asking what is the minimal
 *      distance if 1 tree is planted.
 *      Base case: if all trees are planted, the minimal distance to move trees
 *                  is 0.
 *   
 *  The solution below implements the DP version, with a time complexity of
 *  O(N^2), N being the number of trees.
 * 
 **/

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <iterator>
#include <numeric>
#include <sstream>
#include <vector>

using matrix_t = std::vector<std::vector<double>>;
using tensor_t = std::vector<std::vector<std::vector<double>>>;

double calculate_min_distance(int n_trees, int length, int width, 
                              std::vector<int>& tree_positions);

double euclidean_dist(double x1, double y1, double x2, double y2);

/**
 * @brief Read the input and run the algorithm.
 */
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, L, W;
    double min_distance {0.0};
    std::ostringstream output {};

    while (std::cin >> N){
        std::cin >> L >> W;

        std::vector<int> tree_positions;
        tree_positions.reserve(N);
        std::copy_n(std::istream_iterator<int> (std::cin), N, 
                    std::back_inserter(tree_positions));
        
        min_distance = calculate_min_distance(N, L, W, tree_positions);
        output << std::fixed << std::setprecision(10) << min_distance << "\n";
    }
    std::cout << output.str();
    return 0;
}

/**
 * @brief Compute the Euclidean distance between two points.
 */
double euclidean_dist(double x1, double y1, double x2, double y2){
    return std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));
}

/**
 * @brief Find the minimum distance of moving trees to their plant positions.
 * 
 * @param n_trees: Number of trees to plant. 
 * @param length: Length of the road. 
 * @param width: Width of the road. 
 * @param tree_positions: An array of positions of each tree. 
 * @return double: min distance 
 */
double calculate_min_distance(int n_trees, int length, int width, 
                              std::vector<int>& tree_positions) {
    const double LARGE_NUM {std::numeric_limits<double>::max()};
    int n_pairs {n_trees / 2};
    double spacing {static_cast<double>(length) / (n_pairs - 1)};

    std::ranges::sort(tree_positions);

    // min_distances[0..1][0..n_pairs+1][0..n_pairs+1]
    tensor_t min_distances 
        (2, matrix_t (n_pairs+1, std::vector<double> (n_pairs+1, -1)));
    
    // all trees planted, hence nothing to move.
    min_distances.at(0).at(n_pairs).at(n_pairs) = 0;
    min_distances.at(1).at(n_pairs).at(n_pairs) = 0;

    int tree_pos;
    double x, y;
    for(int l {n_pairs}; l >= 0; l--){
        for(int r {n_pairs}; r >= 0; r--){
            if(l + r == n_trees) continue;

            tree_pos = tree_positions.at(l+r);

            x = l+1 > n_pairs ? LARGE_NUM : min_distances.at(0).at(l+1).at(r) + 
                euclidean_dist(tree_pos, 0, (spacing*l), 0);
            y = r+1 > n_pairs ? LARGE_NUM : min_distances.at(0).at(l).at(r+1) + 
                euclidean_dist(tree_pos, 0, (spacing*r), width);

            if(min_distances.at(0).at(l).at(r) == -1){
                min_distances.at(0).at(l).at(r) = std::min(x, y);
            }

            if(min_distances.at(1).at(l).at(r) == -1){
                min_distances.at(1).at(l).at(r) = std::min(x, y);
            }
        }
    }
    
    return min_distances.at(0).at(0).at(0);
}
// ============== END OF FILE ==============

