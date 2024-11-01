/**
 * unionfind.cpp
 * ------------------
 * Description:
 *  Implementation file containing definitions for the unionfind data structure. 
 *  
 *  This data structure stores a number of sets, and provides functionality to merge
 *  two sets, as well as checking whether two elements belong to the same set.
 *  Internally, a set is represented as a tree with a root. Initially each element 
 *  belongs to its own set and thus is a parent of its own tree. When two sets are
 *  merged, the smaller tree becomes a child of the larger tree.
 * 
 *  Since the trees are being balanced, these operations have an amortized O(log n)
 *  time complexity.
 * */

#include "unionfind.hpp"

/**
 * @brief Construct a new UnionFind:: UnionFind object.
 *        Initially each element belongs to their own sets of size 1.
 * 
 * @param n: number of elements 
 */
UnionFind::UnionFind(int n)
    : N{n}, parents{std::make_unique<int[]>(n)}, sizes{std::make_unique<int[]>(n)}
    {
        for(int i = 0; i < n; i++){
            parents[i] = i;
            sizes[i] = 1;
        }
    }

/**
 * @brief Take the union of the two sets containing x and y respectively.
 *        The smaller set will become a child of the larger tree set.
 * 
 * @param x: first element 
 * @param y: second element 
 */
void UnionFind::join(int x, int y){
    int x_parent = find(x);
    int y_parent = find(y);

    if(sizes[x_parent] <= sizes[y_parent]){
        parents[x_parent] = y_parent;
        sizes[y_parent] += sizes[x_parent];
    }
    else{
        parents[y_parent] = x_parent;
        sizes[x_parent] += sizes[y_parent];
    }
}

/**
 * @brief Test whether two elements belong to the same set.
 * 
 * @param x: first element 
 * @param y: second element
 * @return true: if both elements have the same root. 
 * @return false: if both elements have different roots.
 */
bool UnionFind::same(int x, int y){
    int x_parent = find(x);
    int y_parent = find(y);
    return x_parent == y_parent;
}

/**
 * @brief Find and return the set that x belongs to. It returns the root of the tree set.
 * 
 * @param x: en element 
 * @return int: the root of the tree set x belongs to.
 */
int UnionFind::find(int x){
    int elem {x};
    while(parents[elem] != elem){
        parents[elem] = parents[parents[elem]];  // makes tree flat
        elem = parents[elem];
    }

    return elem;
}
// ============== END OF FILE ==============

