/**
 * segment_tree.hpp
 * ----------------
 * Description:
 *   Header file containing declarations for the Segment tree algorithm.
 * */

#ifndef SEGMENT_TREE_HPP
#define SEGMENT_TREE_HPP

#include <iostream>
#include <functional>
#include <vector>


using ll_t = long long;

template <typename T>
class RangeQuery {
    public:
        explicit RangeQuery(const std::vector<T>& data,
                            std::function<T(T, T)>  comparator);
        virtual ~RangeQuery();
        void update(std::size_t index, T value);
        T query(std::size_t from, std::size_t to);
        virtual void dummy() = 0;  // pure virtual, making class abstract.
    private:
        std::size_t _size;
        std::vector<T> _tree;
        std::function<T(T, T)>  _comparator;
};

template <typename T>
class RangeMaxQuery : public RangeQuery<T> {
    public:
        explicit RangeMaxQuery(const std::vector<T>& data);
        void dummy() override {};
        // ~RangeMaxQuery();
};

template <typename T>
class RangeMinQuery : public RangeQuery<T> {
    public:
        explicit RangeMinQuery(const std::vector<T>& data);
        void dummy() override {};
        // ~RangeMinQuery();
};

#endif

// ============== END OF FILE ==============

