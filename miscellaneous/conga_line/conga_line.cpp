/**
 * conga_line.cpp
 * ------------------
 * Description:
 *   Header file containing definitions for the `Conga Line` problem. 
 * */
#include <algorithm>
#include <iterator>
#include "conga_line.hpp"

/**
 * @brief Concatenate both names of a couple.
 * 
 * @param p: A pair of names.
 * @param reverse: whether to reverese the order of the couple's names.
 */
std::string make_key(const person_t& p, bool reverse = false) {
  if(reverse) {
    return p.second + p.first;
  }
  return p.first + p.second;
}

/**
 * @brief Print the elements of a linked list.
 * 
 * Only the name of the person itself is printed, not their partners too.
 * 
 * @param line: The linked list.
 * @param os: Output stream to print to.
 */
void print_list(line_t& line, std::ostream& os) {
  std::ranges::transform(line, 
    std::ostream_iterator<std::string>(os, "\n"), 
    [&line](const person_t& el){return el.first;}
    );
}

/**
 * @brief Read the input and solve the problem. Print out the solution.
 * 
 */
void main_program() {
  unsigned int n_couples;
  unsigned int n_instructions;
  std::string instructions;
  line_t line;
  line_t::iterator it;
  person_it_map_t person_map;
  std::string name1;
  std::string name2;
  person_t p1, p2;
  std::ostringstream called_names {};

  std::cin >> n_couples >> n_instructions;  
  unsigned int n_persons {2 * n_couples};

  for(unsigned int i = 0; i < n_persons; i+=2){
    std::cin >> name1 >> name2;
    p1 = std::make_pair(name1, name2);
    p2 = std::make_pair(name2, name1);
    it = line.insert(line.end(), p1);
    person_map[make_key(p1)] = it; 
    it = line.insert(line.end(), p2);
    person_map[make_key(p2)] = it;  
  }

  std::cin >> instructions;

  solve_problem(instructions, line, called_names, person_map);

  std::cout << called_names.str() << "\n";
  print_list(line);
}

/**
 * @brief Solve the Conga line problem by executing all instructions.
 * 
 * @param instructions: String of instructions.
 * @param line: The linked list.
 * @param called_names: Output stream of the called names.
 */
void solve_problem(std::string& instructions, 
  line_t& line, 
  std::ostringstream& called_names, 
  person_it_map_t person_map
  ) {
  line_t::iterator curr_it {line.begin()};
  line_t::iterator temp_it;
  line_t::iterator behind_partner_it;
  line_t::iterator self_it;


  for(char& instruction: instructions){
    switch (instruction){
      case 'F':
        curr_it = std::prev(curr_it);
        break;

      case 'B':
        curr_it = std::next(curr_it);
        break;

      case 'R':
        temp_it = std::next(curr_it);
        if(temp_it == line.end()){
          curr_it = line.begin();
        }
        else{
          self_it = line.insert(line.end(), *curr_it);
          person_map[make_key(*self_it)] = self_it;
          line.erase(curr_it);
          curr_it = temp_it;
        }
        break;

      case 'C':
        temp_it = std::next(curr_it);
        if(temp_it == line.end()){
          temp_it = line.begin();
        }

        behind_partner_it = std::next(person_map[make_key(*curr_it, true)]);
        self_it = line.insert(behind_partner_it, *curr_it);
        person_map[make_key(*self_it)] = self_it;
        line.erase(curr_it);
        curr_it = temp_it;
        break;

      case 'P':
        called_names << (*curr_it).second << "\n";
        break;
    }
  }
}

// ============== END OF FILE ==============
