/**
 * bit.cpp
 * ------------------
 * Description:
 *  Implementation file containing definitions for the Binary Indexed Tree (BIT) data structure. 
 *  
 *  It is a data structure for efficient range sum query and update of array elements.
 *  The class below has two methods, add(index, delta) which increments an array element
 *  at a given index with some delta value, and sum(index) which returns the sum of all
 *  array elements starting from 0 up to index-1.
 *  
 * */

#include "bit.hpp"

/**
 * @brief Construct a new BIT::BIT object
 * 
 * @param n: Number of array elements. 
 */
BIT::BIT(std::size_t n)
    : N{n+1}, tree(n+1) {}

BIT::~BIT(){}

/**
 * @brief Incrementing an element in the array.
 * 
 * @param index: position of element 
 * @param delta: value to increment by. 
 */
void BIT::add(std::size_t index, int delta){
    checkIndex(index);
    index += 1;  // adjusting to the tree size
    while(index < N){
        tree.at(index) += delta;
        index += index & -index;  // adding the last set bit of index to index
    }
}

/**
 * @brief Query the sum of array elements from position 0 up to index-1.
 * 
 * @param index: an index to query the cumulative sum at. 
 * @return long long int: the cumulative sum. 
 */
long long int BIT::sum(std::size_t index) const{
    checkIndex(index);
    long long int sum {0};

    while(index > 0){
        sum += tree.at(index);
        index -= index & -index;  // unsetting the last set bit of index
    }

    return sum;
}

/**
 * @brief Print the binary indexed tree.
 * 
 * @param os: output stream 
 * @param data: a tree. 
 * @return std::ostream& 
 */
std::ostream& operator<<(std::ostream& os, const BIT& data){
   std::copy(data.tree.begin(), data.tree.end(), std::ostream_iterator<int>(os, " "));
    return os;
}

/**
 * @brief Check whether a given index is within range.
 * 
 * @param index 
 */
constexpr void BIT::checkIndex(std::size_t index) const{
    if(index > N){
        throw std::out_of_range("Index" + std::to_string(index) + " is out of range.");
    }
}

// ============== END OF FILE ==============

