/**
* main.cpp
 * -----------------
 * Ljutnja (https://open.kattis.com/problems/ljutnja):
 *  Given a list of number of desired candies for N children, and a bag of M candies,
 *  determine how big the anger will be among the children if they receive less than
 *  the desired amount. The total anger is sum of anger of each children, where the 
 *  anger is (desired - received)^2. The task is to distribute the candies such as to
 *  minimize the total anger. 
 *
 * Solution:
 *  We can use the insight that 1^2 + 1^2 < 0^2 + 2^2 (2 candies shortage), or that  
 *  1^2 + 1^2 + 2^2 < 1^2 + 3^2 (4 candies shortage). In general, the more evenly the 
 *  shortage is distributed among the chilrden, the smaller the total anger will be.
 *  A simple solution is to remove 1 candie from each childen while there is shortage,
 *  however this is slow due to the fact that shortage can be very large. 
 * 
 *  The solution below uses a greedy approach, where the chilren desires are sorted
 *  in ascending order, then for each child, distribute the remaining shortage
 *  among the remaining children, and let current child pay a price. This way, we are 
 *  certain that no chil pays too much, but also that we are sure that the remaining
 *  children will be able to together pay the remaining shortage.
 *  
 *  This solution has a N * log(N) time complexity, where N is number of children.
 *   
 *
 **/
 
#include <iostream>
#include <algorithm>
#include <cmath>
#include <iterator>
#include <numeric>
#include <sstream>
#include <vector>

using ull_t = unsigned long long int;

ull_t calculate_min_anger(std::vector<unsigned int>& children_desires,  
                          unsigned int n_candies, 
                          unsigned int n_children);

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n_children, n_candies;

    ull_t min_anger;
    std::ostringstream output {};

    while(std::cin >> n_candies >> n_children){
        std::vector<unsigned int> children_desires (n_children);
        for(unsigned int i {0}; i < n_children; i++){
            std::cin >> children_desires.at(i);
        }
        min_anger = calculate_min_anger(children_desires, n_candies, n_children);
        output << min_anger << "\n";
    }

    std::cout << output.str();
    
    return 0;
}

/**
 * @brief Calculate the sum of anger of all children.
 * 
 * @param children_desires: vector of candie desires of each child. 
 * @param n_candies: number of candies 
 * @param n_children: number of children 
 * @return ull_t total_anger
 */
ull_t calculate_min_anger(std::vector<unsigned int>& children_desires, 
                          unsigned int n_candies, 
                          unsigned int n_children){
    ull_t total_anger {0};
    ull_t total_desired_candies {std::accumulate(children_desires.begin(), 
                                                 children_desires.end(), 
                                                 0ULL)};
    ull_t candies_shortage {total_desired_candies - n_candies};
    if(candies_shortage <= children_desires.size()) return candies_shortage;

    std::ranges::sort(children_desires);
    
    ull_t balanced_deprivation, deprivation;
    unsigned int child_desire, remaining_children;

    for(unsigned int i {0}; i < n_children; i++){
        child_desire = children_desires.at(i);
        remaining_children = n_children - i;
        // balanced_deprivation = math.ceil(candies_shortage/remaining_chilrden)
        balanced_deprivation = (candies_shortage + remaining_children - 1) / remaining_children;
        deprivation = child_desire <= balanced_deprivation ? child_desire : balanced_deprivation;
        total_anger += deprivation*deprivation;
        candies_shortage -= deprivation;
    }
    
    return total_anger;
}

// ============== END OF FILE ==============

