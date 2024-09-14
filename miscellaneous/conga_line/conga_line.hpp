/**
 * conga_line.hpp
 * ------------------
 * Description:
 *   Header file containing declarations for the `Conga Line` problem. 
 * */

#ifndef CONGA_LINE_HPP
#define CONGA_LINE_HPP

#include <iostream>
#include <sstream>
#include <string> 
#include <list>
#include <unordered_map>
#include <utility>

using person_t = std::pair<std::string, std::string>;
using line_t = std::list<person_t>;
using person_it_map_t = std::unordered_map<std::string, line_t::iterator>;

void print_list(line_t& line, std::ostream& os = std::cout);

void main_program();

void solve_problem(std::string& instructions, 
  line_t& line, 
  std::ostringstream& called_names, 
  person_it_map_t person_map);

#endif // CONGA_LINE_HPP