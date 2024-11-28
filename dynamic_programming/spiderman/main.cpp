/** 
* main.cpp
 * -----------------
 * Spiderman's Workout (https://open.kattis.com/problems/spiderman):
 *  Given a list of distances, Spiderman can either climb up or down each of these
 *  distances on some building. However, since he starts at ground level, the first move
 *  must be up, and, similarly, the last move must get him back to ground level. Thus
 *  the last move must be down. Additionally, the building height must be as low as possible.
 *  The task is to determine a path of upp's and down's that satisfy these constraints, 
 *  or indicate that it is impossible to find such a path. 
 *
 * Solution:
 *  This problem is similar to the Knapsack problem. The first step is to find a recursive
 *  formula that solves the problem. Then adding a memoization step to remove repeated 
 *  computations, or use a tabular method instead. The solution below uses a table of heights
 *  for each [step, height] pair, where the required height climbed for a path is stored in it.
 *  Then we traverse it to find the path with the lowest required height.   
 *
 **/
 
#include <iostream>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

std::vector<char> spiderman(const std::vector<int>& distances);

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::size_t n_tests;
    std::size_t n_distances;
    std::string line;

    std::cin >> n_tests;

    for(std::size_t test_case {0}; test_case < n_tests; test_case++){
        std::cin >> n_distances;
        std::getline(std::cin >> std::ws, line);
        std::istringstream iss {line};
        std::vector<int> distances {std::istream_iterator<int>(iss), std::istream_iterator<int> {}};
        
        std::vector<char> path {spiderman((distances))};
        if(path.at(0) == 'D') std::cout << "IMPOSSIBLE\n";
        else{
            std::ranges::copy(path, std::ostream_iterator<char> (std::cout, ""));
            std::cout << "\n";
        }
    }
    std::cout << std::endl;
    return 0;
}

std::vector<char> spiderman(const std::vector<int>& distances){
    std::size_t n_distances {distances.size()};
    std::vector<char> path (n_distances, 'D');
    
    int DIST_SUM {std::accumulate(distances.begin(), distances.end(), 0)};
    int MAX_HEIGHT {DIST_SUM / 2};
    int LARGE_NUM {MAX_HEIGHT + 1};
    
    if(DIST_SUM % 2 == 1 || n_distances < 2 || distances.at(n_distances-1) > MAX_HEIGHT){
        return path;
    }

    std::vector<std::vector<int>> heights (n_distances, std::vector<int> (MAX_HEIGHT+1, 0));
    std::ranges::fill(heights.at(n_distances-1), LARGE_NUM);
    heights.at(n_distances-1).at(distances.at(n_distances-1)) = distances.at(n_distances-1);
    
    int d, u, dist;

    for(std::size_t step {n_distances-2}; ; step--){
        dist = distances.at(step);
        for(int height {0};  height <= MAX_HEIGHT; height++){
            d = height-dist < 0 ? LARGE_NUM : heights.at(step+1).at(height-dist);
            u = height+dist > MAX_HEIGHT ? LARGE_NUM : heights.at(step+1).at(height+dist);
            heights.at(step).at(height) = std::min(std::max(d, height), std::max(u, height));
        }
        if(step == 0) break;
    }

    int min_height = heights.at(0).at(0);
    if(min_height > MAX_HEIGHT) return path;

    int h {0};
    for(std::size_t i {0}; i < n_distances-1; i++){
        dist = distances.at(i);
        d = h-dist < 0 ? LARGE_NUM : heights.at(i+1).at(h-dist);
        u = h+dist > MAX_HEIGHT ? LARGE_NUM : heights.at(i+1).at(h+dist);
        path.at(i) = u <= d ? 'U' : 'D';
        h += u <= d ? dist : -dist;
    }
    return path;
}

// ============== END OF FILE ==============

