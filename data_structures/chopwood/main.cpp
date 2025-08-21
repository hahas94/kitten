/**
* main.cpp
 * -----------------
 * Chopping Wood (https://open.kattis.com/problems/chopwood):
 *  The edges of an unrooted, undirected and acyclic graph are remove one at
 *  a time, always removing the edge with the lowest leaf vertex.
 *  Given is a list of the parent vertices, and asked is the leaf vertices
 *  of the edges removed.
 *
 * Solution:
 *  We can use the Union Find data structure to create the tree step by step,
 *  for each edge finding the leaf node of it with the help of the previous
 *  parent vertex, while keeping track of the possibility of illegal vertices
 *  occurring.
 *
 **/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <print>
#include <string>
#include <sstream>
#include <unordered_set>
#include <vector>
#include "../../algorithms/unionfind.hpp"

std::string generate_lost_column(const std::vector<int>& v_column,
                                 int largest_vertex);

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    std::ostringstream oss;

    while (std::cin >> N) {
        std::vector<int> v_column;
        v_column.reserve(N);
        std::copy_n(std::istream_iterator<int> (std::cin), N,
                    std::back_inserter(v_column));

        oss << generate_lost_column(v_column, N + 1);
    }
    std::cout << oss.str();
    
    return 0;
}

std::string generate_lost_column(const std::vector<int>& v_column,
                                 const int largest_vertex) {
    const std::string error_ans = "Error\n";

    int largest_remaining_vertex {largest_vertex - 1};
    if (v_column.back() != largest_vertex) return error_ans;

    std::size_t index {v_column.size() - 1};
    std::vector<int> u_column (v_column.size());
    std::unordered_set<int> discarded_vertices (v_column.back());
    std::unordered_set<int> remaining_vertices (v_column.back());
    for (int i {1}; i <= v_column.back(); i++) {remaining_vertices.insert(i);}
    UnionFind tree(largest_vertex + 1);

    while (index >= 1) {
        while (discarded_vertices.contains(largest_remaining_vertex)) {
            largest_remaining_vertex--;
        }
        // handle all edges except the first
        const int prev = v_column[index - 1];
        const int curr = v_column[index];

        if (tree.same(prev, curr)) {
            if (largest_remaining_vertex == curr) return error_ans;
            tree.join(largest_remaining_vertex, curr);
            discarded_vertices.insert(curr);
            discarded_vertices.insert(largest_remaining_vertex);
            remaining_vertices.erase(curr);
            remaining_vertices.erase(largest_remaining_vertex);
            u_column[index] = largest_remaining_vertex;
        } else {
            tree.join(curr, prev);
            discarded_vertices.insert(curr);
            discarded_vertices.insert(prev);
            remaining_vertices.erase(curr);
            remaining_vertices.erase(prev);
            u_column[index] = prev;
        }
        index--;
    }
    // handle the first edge
    if (remaining_vertices.size() == 1 &&
        !discarded_vertices.contains(*remaining_vertices.begin())) {
        u_column[index] = *remaining_vertices.begin();
    } else { return error_ans; }

    std::ostringstream ans;
    for (std::size_t i {0}; i < u_column.size(); i++) {ans << u_column[i] << "\n";}

    return ans.str();
}

// ============== END OF FILE ==============
