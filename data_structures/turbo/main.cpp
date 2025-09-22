/**
* main.cpp
 * -----------------
 * Turbo (https://open.kattis.com/problems/turbo):
 *  Given an array of distinct integers {1, 2, ..., N}, sort them
 *  through swapping elements, in the order 1, N, 2, N-1, 3, N-2 ...etc.
 *  count the number of swaps required for sorting each element.
 *
 * Solution:
 *  Given a binary indexed tree of only 1's of size N and an element to
 *  be sorted, we can count the number of elements to its left or right
 *  (and to the end of the tree) that are still active by making a sum query.
 *  This gives us the number of swaps needed. Then make that element inactive
 *  by turning it into 0 in the tree, meaning removing it from the tree.
 *
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
            tree.add(index - 1, -1);
            oss << dist << "\n";
            counter++;
        }
        std::cout << oss.str();
    }

    return 0;
}

// ============== END OF FILE ==============

