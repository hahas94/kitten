/**
* main.cpp
 * -----------------
 * Graduation (https://open.kattis.com/problems/skolavslutningen):
 *   Given an arrangement of students into rows and columns, where each student belongs to
 *   a class, find the maximum number of unique hat colors that can be given to the students
 *   subject to the constraints that each column and class each must have identical hats 
 *   respectively.
 *
 * Solution:
 *   This is an optimization problem, where a brute-force way of solving it is to color a column,
 *   then for all the other columns that have a class intersection with this column, assign them as
 *   colored. Repeat this process until no column remain uncolored.
 *
 **/

#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <set>

int main(){
	std::size_t n_rows, n_cols, n_classes;
	std::cin >> n_rows >> n_cols >> n_classes;
	std::unordered_map<int, std::set<char>> columns_classes (n_cols);

	std::string row; 

	for(std::size_t i = 0; i < n_rows; i++){
		std::cin >> row;
		for(std::size_t j = 0; j < n_cols; j++){
			columns_classes[j].insert(row.at(j));
		}
	}
	
	int n_colors {};
	std::set<char> colored_classes;
	std::set<int> colored_columns;
	std::set<char> intersected_classes;
	std::size_t prev_size {0};
	std::set<char> column;

	for(std::size_t col = 0; col < n_cols; col++){
		if(colored_classes.size() == n_classes || colored_columns.size() == n_cols){
			break;
		}

		column = columns_classes.at(col);
		prev_size = colored_classes.size();
		std::ranges::set_union(colored_classes, 
			column, 
			std::inserter(colored_classes, colored_classes.end())
			);

		if(prev_size < colored_classes.size() && !colored_columns.contains(col)){
			colored_columns.insert(col);
			n_colors++;
		}
			
		for(std::size_t next_col = col + 1; next_col < n_cols; next_col++){
			column = columns_classes.at(next_col);
			std::ranges::set_intersection(colored_classes, 
				column, 
				std::inserter(intersected_classes, intersected_classes.begin())
				);
			if(intersected_classes.size() > 0){
				colored_columns.insert(next_col);
				std::ranges::set_union(colored_classes, 
					column, 
					std::inserter(colored_classes, colored_classes.end())
					);
			}
			intersected_classes.clear();
		}
	}

	std::cout << n_colors << std::endl;

	return 0;
}

// ============== END OF FILE ==============