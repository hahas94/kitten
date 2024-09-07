/**
* reverse_binary.cpp
 * -----------------
 * Reversed Binary Numbers (https://open.kattis.com/problems/reversebinary):
 *   Given a number, return the number corresponding to the reverse
 *   of the binary representation of it.
 *
 * Solution:
 *   Read input, find its binary representation, reverse it, find the corresponding
 *   number and return.
 *
 **/

#include <iostream>
#include <cmath>
#include <bitset>
#include <algorithm>
#include "reverse_binary.hpp"

int main() {
  unsigned long num;
  std::cin >> num;
  std::string binary_number {to_binary(num)};
  std::ranges::reverse(binary_number);
  unsigned long decimal {to_decimal(binary_number)};
  std::cout << decimal << std::endl;
  return 0; 
}

/**
 * @brief Find the number of bits of the binary representation of a number.
 *
 * @param num: a positive integer
 * @return n_bits: length of binary representation of input number
 */
int bit_length(unsigned long num){
  int n_bits{1};

  while(std::pow(2, n_bits) <= num){
    n_bits++;
  }

  return n_bits;
}

/**
 * @brief Convert a number to its binary representation.
 * 
 * The method uses successive division by 2 until reaching 0.
 *
 * @param num: a positive integer
 * @return string_repr: string of binary representation of input number
 */
std::string to_binary(unsigned long num){

  std::bitset<30> bits;

  unsigned long rest {};
  int n_bits {bit_length(num)};

  while (num > 0){
    rest = num % static_cast<unsigned long>(std::pow(2, n_bits - 1));
    
    bits.set(n_bits - 1, true);
    num = rest;
    n_bits = bit_length(num);
  }

  std::string result {bits.to_string()};
  std::size_t first_one {result.find_first_of('1')};
  
  if(first_one != std::string::npos){
    result = result.substr(first_one, result.size());
  }
  else{
    result = "0";
  }

  return result;
}

/**
 * @brief Convert a binary number to its decimal representation.
 *
 * @param num: a binary number in its string representation
 * @return decimal_number: decimal representation of the binary number
 */
unsigned long to_decimal(std::string binary_number){
  unsigned long result {0};
  unsigned long num_bits{binary_number.length()};

  for(unsigned long pos = 0; pos <= num_bits - 1; pos++){
    if(binary_number.at((num_bits - 1) - pos) == '1'){
      result = result + std::pow(2, pos);
    }
  }

  return result;
}

// ============== END OF FILE ==============
