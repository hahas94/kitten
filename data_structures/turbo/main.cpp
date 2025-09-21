/**
* main.cpp
 * -----------------
 * Turbo (https://open.kattis.com/problems/turbo):
 *   
 *
 * Solution:
 * [6, 3, 4, 1, 5, 2, 8, 7]
 * [1, 1, 1, 1, 1, 1, 1, 1]
 * 1:  [1, 1, 1, 0, 1, 1, 1, 1] (3)
 * 8:  [1, 1, 1, 0, 1, 1, 0, 1] (1)
 * 2:  [1, 1, 1, 0, 1, 0, 0, 1] (4)
 * 7:  [1, 1, 1, 0, 1, 0, 0, 0] (0)
 * 3:  [1, 0, 1, 0, 1, 0, 0, 0] (1)
 * 6:  [1, 0, 1, 0, 1, 0, 0, 0] (1)
 **/

#include <iostream>
#include <sstream>
#include <vector>

#include "../../algorithms/bit.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    int element;
    while (std::cin >> N) {
        std::ostringstream oss;

        std::vector<int> positions (N+1, 1);
        for (int i = 1; i <= N; i++) {
            std::cin >> element;
            positions[element] = i;
        }

        BIT tree (N);
        for (int i {0}; i < N; i++) {
            tree.add(i, 1);
        }

        int left_ptr {1};
        int right_ptr {N};
        int counter {1};
        int dist;
        int index;

        while (counter <= N) {
            if (counter % 2 == 1) {
                index = positions[left_ptr];
                dist = tree.sum(index - 1);
                left_ptr++;
            } else {
                index = positions[right_ptr];
                dist = tree.sum(N) - tree.sum(index);
                right_ptr--;
            }
            // std::cout << tree << "\n";
            tree.add(index - 1, -1);
            oss << dist << "\n";
            counter++;
        }
        std::cout << oss.str();
    }

    return 0;
}

// ============== END OF FILE ==============

