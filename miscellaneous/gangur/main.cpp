/**
* main.cpp
 * -----------------
 * Gangur (https://open.kattis.com/problems/gangur):
 * 	Given an array of people's directions L, R or no direction,
 * 	find the total number of times people of opposing direction will
 * 	face each other if they were to walk from their position to the 
 * 	end position in the direction they are facing.
 * 
 * Solution:
 * 	We can compute the partial sums for each L facing people. The sum of
 * 	all of them is the final result. 
 *   
 *
 **/

#include <iostream>
#include <string>


unsigned long int find_num_meetings(const std::string& peoples);

int main(){
	std::string peoples;
	std::cin >> peoples;
	std::cout << find_num_meetings(peoples) << std::endl;
	return 0;
}

unsigned long int find_num_meetings(const std::string& peoples){
	unsigned long result {0};
	unsigned int num_right {0};

	for(const char& s: peoples){
		if(s == '>'){
			num_right++;
		}
		else if(s == '<'){
			result += num_right;
		}
	}

	return result;
}

// ============== END OF FILE ==============
