/**
* main.cpp
 * -------
 * Introspective Caching (https://open.kattis.com/problems/caching):
 *  Given a list of elements being accessed, and a cache of a max size,
 *  which elements should be cached at every step to minimize
 *  the total number of elements read from the system.
 *
 * Solution:
 *  We employ a greedy strategy, let's first fill the cache. Then for each
 *  of the remaining elements, we need to discard one element from the cache
 *  and add it instead. The question then becomes which element to discard.
 *  The strategy is to always discard the element accessed after all
 *  the other elements in the cache will be accessed next. That's the last
 *  accessed element, which may possibly be the element not accessed anymore.
 *
 *  How do we find which element is accessed last among the cached elements?
 *  Using a segment tree where we store the position of each element being
 *  accessed next, we can query the max element to get the position, and from
 *  the position we can get the element. Thus this element is discarded.
 *  For elements not being cached currently, their next accessed position is
 *  set to -1, meaning inactive. If an element in the cache is not accessed
 *  anymore, the next accessed position will be a large value, indicating
 *  this element to be discarded next. Such elements are stored in a deque.
 *
 *  This approach will have a time complexity of |A|*log(|N|).
 *
 **/

#include <iostream>
#include <iterator>
#include <deque>
#include <unordered_set>
#include <vector>

#include <segment_tree.hpp>

int count_reads(int n_elements, unsigned cache_size, int n_accesses,
                const std::vector<int>& accessed_elements);

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // Read all inputs, store access list in an array, count min reads.
    int n_elements, cache_size, n_accesses;
    while (std::cin >> cache_size >> n_elements >> n_accesses) {
        std::vector<int> accessed_elements;
        accessed_elements.reserve(n_accesses);
        for (int i {0}; i < n_accesses; i++) {
            int elem;
            std::cin >> elem;
            accessed_elements.push_back(elem);
        }
        std::cout << count_reads(n_elements, cache_size, n_accesses, accessed_elements) << '\n';
    }
    return 0;
}

/**
 * Find the minimal number of reads using a greedy strategy.
 * @param n_elements: Number of unique elements.
 * @param cache_size: Maximum cache size.
 * @param n_accesses: Number of times elements will be accessed.
 * @param accessed_elements: List of accessed elements.
 * @return: Minimal number of reads.
 */
int count_reads(const int n_elements, const unsigned cache_size,
                const int n_accesses,
                const std::vector<int>& accessed_elements) {
    if (n_accesses == 0) return 0;

    int n_reads {0};
    int LARGE_NUM {100000};

    // For each accessed element, we store the positions they are accessed at.
    std::unordered_map<int, std::deque<int>> accessed_at;
    for (int i {0}; i < n_accesses; i++) {
        accessed_at[accessed_elements[i]].push_back(i);
    }

    // The first time an element is accessed is not useful as it is past event.
    for (int i {0}; i < n_elements; i++) {
        if (!accessed_at[i].empty()) accessed_at[i].pop_front();
    }

    std::deque<int> extinct_elems;  // Store elements no longer accessed

    // Given a key element, remove and return the front pos in its deque.
    auto remove_front = [&LARGE_NUM, &accessed_at](const int elem) -> int {
        if (accessed_at[elem].empty()) {
            return LARGE_NUM;
        }
        const int pos {accessed_at[elem].front()};
        accessed_at[elem].pop_front();
        return pos;
    };

    // Simulation of the cache.
    std::unordered_set<int> cache;

    // Vector for the next accessed position of all elements, used in seg-tree.
    std::vector<int> positions (n_elements, -1);

    // Filling the cache initially.
    int i {0};
    while (cache.size() < cache_size && i < n_accesses) {
        const int elem {accessed_elements[i]};
        cache.insert(elem);
        const int next_accessed_pos {remove_front(elem)};
        if (next_accessed_pos == LARGE_NUM) extinct_elems.push_back(elem);
        positions[elem] = next_accessed_pos;
        i++;
    }

    n_reads += static_cast<int> (cache.size());

    // A segment tree for the next accessed positions.
    RangeMaxQuery<int> last_requested_tree (positions);

    // Handling of the remaining accessed elements.
    while (i < n_accesses) {
        const int elem {accessed_elements[i]};
        int next_accessed_pos {remove_front(elem)};
        if (next_accessed_pos == LARGE_NUM) extinct_elems.push_back(elem);

        if (!cache.contains(elem)) {
            const int to_remove_pos {last_requested_tree.query(0, n_elements)};
            int to_remove;
            if (to_remove_pos == LARGE_NUM) {
                to_remove = extinct_elems.front();
                extinct_elems.pop_front();
            } else to_remove = accessed_elements[to_remove_pos];

            cache.erase(to_remove);
            last_requested_tree.update(to_remove, -1);

            cache.insert(elem);
            n_reads++;
        }
        // Update the next accessed pos of elem in the segment-tree.
        last_requested_tree.update(elem, next_accessed_pos);

        i++;

    }
    return n_reads;
}


// ============== END OF FILE ==============

