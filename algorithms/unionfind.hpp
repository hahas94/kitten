/**
 * unionfind.hpp
 * -------------
 * Description:
 *   Header file containing declarations for the unionfind data structure. 
 * */

#ifndef UNIONFIND_HPP
#define UNIONFIND_HPP
 
#include <iostream>
#include <memory>
#include <exception>

class UnionFind{
    public:
        UnionFind(int n);
        ~UnionFind();
        UnionFind(const UnionFind& other);
        UnionFind& operator=(const UnionFind& other);
        UnionFind(UnionFind&& other) noexcept;
        UnionFind& operator=(UnionFind&& other) noexcept;
        int find(int x);
        void join(int x, int y);
        bool same(int x, int y);
        int size() const;

    private:
        int N;
        std::unique_ptr<int[]> parents;
        std::unique_ptr<int[]> sizes;

        constexpr void checkIndex(int index) const;
};

#endif

// ============== END OF FILE ==============

