/**
 * segment_tree.cpp
 * ------------------
 * Description:
 *   Implementation file containing definitions for the Segment tree
 *   data structure.
 *
 *   This data structure finds maximum/minimum elements in range queries
 *   efficiently. It constructs an array twice the size of the input data,
 *   and computes the max/min element by building a (virtual) tree and
 *   recursively compute max/min of two adjacent nodes.
 *   Both finding min/max in a range or updating an element has O(log(n))
 *   time-complexity.
 *
 *  Ex.
 *   data = [6, 10, 5, 2, 7, 1, 0, 9]
 *   tree = [0, 0, 0, 0, 0, 0, 0, 0, 6, 10, 5, 2, 7, 1, 0, 9]
 *   completed_tree = [0, 10, 10, 9, 10, 5, 7, 9, 6, 10, 5, 2, 7, 1, 0, 9]
 *
 *   In tree form:
 *        ------------------------------------------
 *                          10
 *                      10      9
 *                   10   5   7   9
 *                  6 10 5 2 7 1 0 9
 *        ------------------------------------------
 * */

#include "segment_tree.hpp"
#include <utility>

/**
 * Initializing the Segment tree.
 * @param data: The data to perform range queries on.
 * @param comparator: A function for performing comparisons between elements.
 */
template<typename T>
RangeQuery<T>::RangeQuery(const std::vector<T>& data,
                          std::function<T(T, T)>  comparator) :
    _size{data.size()}, _tree (2 * data.size()), _comparator {std::move(comparator)}
    {

    // copy the array to the 2nd half
    std::ranges::copy(data.begin(), data.end(), _tree.begin() + _size);

    // Completing the tree by comparing two child elements
    // of a node, until reaching the root node.
    for (std::size_t i {_size - 1}; i > 0; --i) {
        _tree[i] = _comparator(_tree[2*i], _tree[2*i + 1]);
    }
}

template<typename T>
RangeQuery<T>::~RangeQuery() = default;

/**
 * Updating an element in the array.
 * Recursively update the tree as well.
 * @param index: Original position.
 * @param value: Value to update element with.
 */
template<typename T>
void RangeQuery<T>::update(std::size_t index, const T value) {
    index += _size;
    _tree[index] = value;
    T new_value;

    while (index > 1) {
        index /= 2;
        new_value = _comparator(_tree[2*index], _tree[2*index + 1]);

        if (_tree[index] != new_value) {
            _tree[index] = new_value;
        } else {break;} // no need to continue when there are no more changes.
    }
}

/**
 * Query max/min element in given range.
 * @param from: Start index.
 * @param to: End index (exclusive).
 * @return max/min element in range.
 */
template<typename T>
T RangeQuery<T>::query(std::size_t from, std::size_t to) {
    from += _size;
    to += _size;
    T minmax; // Using different value depending on query type: max or min.
    (_comparator(-1, 1) == 1) ? // min query returns -1 max-query returns 1.
        minmax = {std::numeric_limits<T>::min()} :
        minmax = {std::numeric_limits<T>::max()};

    // Updating `max` for odd indices only, because even indices correspond
    // to the left child of a node, hence we can use the parent value instead.
    while (from < to) {
        if (from % 2 == 1) {
            minmax = _comparator(minmax, _tree[from]);
            from++;
        }
        if (to % 2 == 1) {
            to--;
            minmax = _comparator(minmax, _tree[to]);
        }

        // Move to the next level of the tree.
        from /= 2;
        to /= 2;
    }

    return minmax;
}

// RangeMaxQuery: child class of RangeQuery with max() as comparator.
template<typename T>
RangeMaxQuery<T>::RangeMaxQuery(const std::vector<T> &data) :
    RangeQuery<T>(data, [](T a, T b) { return std::max(a, b); }) {}

//
// template<typename T>
// RangeMaxQuery<T>::~RangeMaxQuery() = default;

// RangeMinQuery: child class of RangeQuery with min() as comparator.
template<typename T>
RangeMinQuery<T>::RangeMinQuery(const std::vector<T> &data) :
    RangeQuery<T>(data, [](T a, T b) { return std::min(a, b); }) {}

// template<typename T>
// RangeMinQuery<T>::~RangeMinQuery() = default;

// Explicitly defining the object templates for some common data types.

template class RangeQuery<int>;
template class RangeQuery<double>;
template class RangeQuery<float>;

template class RangeMaxQuery<int>;
template class RangeMaxQuery<double>;
template class RangeMaxQuery<float>;

template class RangeMinQuery<int>;
template class RangeMinQuery<double>;
template class RangeMinQuery<float>;

// ============== END OF FILE ==============

