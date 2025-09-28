/**
 * unionfind.cpp
 * ------------------
 * Description:
 *  Implementation file containing definitions for the unionfind data structure. 
 *  
 *  This data structure stores a number of sets, and provides functionality to
 *  merge two sets, as well as checking whether two elements belong to the same
 *  set. Internally, a set is represented as a tree with a root. Initially,
 *  each element belongs to its own set and thus is a parent of its own tree.
 *  When two sets are merged, the smaller tree becomes a child of the larger
 *  tree.
 *  Since the trees are being balanced, these operations have an amortized
 *  O(log n) time complexity.
 * */

#include "unionfind.hpp"

/**
 * @brief Construct a new UnionFind:: UnionFind object.
 *        Initially, each element belongs to their own sets of size 1.
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

UnionFind::~UnionFind(){
    // Included for interface completeness.
}


/**
 * @brief Copy constructor operator.
 * 
 * @param other: an object to deep copy. 
 */
UnionFind::UnionFind(const UnionFind& other)
    : N{other.size()}, parents{std::make_unique<int[]>(other.size())}, 
      sizes{std::make_unique<int[]>(other.size())}
    {
        for(int i = 0; i < N; i++){
            parents[i] = other.parents[i];
            sizes[i] = other.sizes[i];
        }
    }

/**
 * @brief Copy assignment operator.
 * 
 * @param other: object to copy 
 * @return UnionFind&: the object itself 
 */
UnionFind& UnionFind::operator=(const UnionFind& other){
    if(this != &other){
        UnionFind temp {other};
        std::swap(N, temp.N);
        std::swap(parents, temp.parents);
        std::swap(sizes, temp.sizes);
    }

    return *this;
}

/**
 * @brief Move constructor operator.
 * 
 * @param other: temporary UnionFind object 
 */
UnionFind::UnionFind(UnionFind&& other) noexcept
    : N{other.N}, parents{std::move(other.parents)}, sizes{std::move(other.sizes)} {
        other.N = 0;
    }

/**
 * @brief Move assignment operator
 * 
 * @param other: a temporary object to steal content from. 
 * @return UnionFind& 
 */
UnionFind& UnionFind::operator=(UnionFind&& other) noexcept{
    if(this != &other){
        N = other.N;
        parents = std::move(other.parents); 
        sizes = std::move(other.sizes);
        other.N = 0;
    }

    return *this;
}

/**
 * @brief Find and return the set that x belongs to. It returns the root of the tree set.
 * 
 * @param x: en element 
 * @throws std::out_of_range: if x is out of range
 * @return int: the root of the tree set x belongs to.
 */
int UnionFind::find(int x){
    checkIndex(x);
    
    int elem {x};
    while(parents[elem] != elem){
        parents[elem] = parents[parents[elem]];  // makes tree flat
        elem = parents[elem];
    }

    return elem;
}

/**
 * @brief Take the union of the two sets containing x and y respectively.
 *        The smaller (in height) set will become a child of the larger tree set.
 * 
 * @param x: first element 
 * @param y: second element 
 */
void UnionFind::join(int x, int y){
    int x_parent = find(x);
    int y_parent = find(y);

    if (x_parent == y_parent) return;

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
 * @brief Return total number of elements.
 * 
 * @return int: number of elements 
 */
int UnionFind::size() const{
    return N;
}

/**
 * @brief Check that an index is within range. Throw out of range error if it fails.
 * 
 * @param index 
 */
constexpr void UnionFind::checkIndex(int index) const {
    if (index >= N || index < 0) {
        throw std::out_of_range("Index" + std::to_string(index) + " is out of range.");
    }
}

// ============== END OF FILE ==============

