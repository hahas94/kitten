/**
 * bit.hpp
 * -------
 * Description:
 *   Header file containing declarations for the Binary Indexed Tree (BIT) data structure. 
 * */

#ifndef BIT_HPP
#define BIT_HPP
 
#include <iostream>
#include <algorithm>
#include <iterator>
#include <exception>
#include <vector>

class BIT{
    public:
        BIT(std::size_t n);
        ~BIT();
        void add(std::size_t index, int delta);
        long long int sum(std::size_t index) const;
        friend std::ostream& operator<<(std::ostream& os, const BIT& data);   
    private:
      std::size_t N;
      std::vector<long long int> tree; 

      constexpr void checkIndex(std::size_t index) const;
};

#endif

// ============== END OF FILE ==============

