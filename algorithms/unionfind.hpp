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

class UnionFind{
    public:
        UnionFind(int n);
        void join(int x, int y);
        bool same(int x, int y);

    private:
        int N;
        std::unique_ptr<int[]> parents;
        std::unique_ptr<int[]> sizes;

        int find(int x);
};

#endif

// ============== END OF FILE ==============

