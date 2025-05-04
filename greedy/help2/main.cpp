/**
* main.cpp
 * -----------------
 * Help! (https://open.kattis.com/problems/help2):
 *  Given two patterns, find a phrase matching both of them, or determine
 *  if no such phrase exists. A pattern is a line containing words and 
 *  placeholdders, where a placeholder can be replaced by a word. The task
 *  is to replace all placeholders with words in order to make a phrase.   
*
 * Solution:
 *  Start solution by treating each adjacent pairs of strings. While not all 
 *  placeholders have been treated, start looping over the patterns. 
 *  Each time a change is made to either patterns, restart the loop. This
 *  because earlier pairs may be dependent on the latest change, hence the need
 *  to restart. A change is either an explicit correspondence between a word and
 *  a placeholder, or an implicit one based on earlier
 *  detected changes, where the change has been recorded in maps.
 * 
 *  Once all pairs of strings have been treated, the only strings that are
 *  still placeholders are those for whom no word exists, thus replace those
 *  with an arbitrary string. 
 *
 **/
 
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

using phrase_t = std::vector<std::string>;

phrase_t make_pattern(std::string& line);
phrase_t find_phrase(phrase_t& pattern1, phrase_t& pattern2);
void print_phrase(const phrase_t& phrase);

/**
 * Reading input, running test cases and printing solution.
 */
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    phrase_t pattern1;
    phrase_t pattern2;
    phrase_t phrase;
    std::string line1;
    std::string line2;

    int n_tests;
    std::cin >> n_tests;
    for(int i = 0; i < n_tests; i++){
        std::getline(std::cin >> std::ws, line1);
        std::getline(std::cin >> std::ws, line2);
        pattern1 = make_pattern(line1);
        pattern2 = make_pattern(line2);
        phrase = find_phrase(pattern1, pattern2);
        print_phrase(phrase);
    }
    
    return 0;
}

/**
 * @brief Creates a vector of strings from a string, separating words by space.
 * 
 * @param line: a string line 
 * @return phrase_t: vector of strings 
 */
phrase_t make_pattern(std::string& line){
    std::istringstream iss {line};
    phrase_t pattern {std::istream_iterator<std::string>(iss),
                          std::istream_iterator<std::string> {}};
    
    return pattern;
}

/**
 * @brief Runs an algorithm to find a phrase matching two patterns.
 * 
 * Start solution by treating each adjacent pairs of strings. While not all 
 * placeholders have been treated, start looping over the patterns. 
 * Each time a change is made to either patterns, restart the loop. This
 * because earlier pairs may be dependent on the latest change, hence the need
 * to restart. A change is either an explicit correspondence between a word and
 * a placeholder, or an implicit one based on earlier
 * detected changes, where the change has been recorded in maps.
 * 
 * Once all pairs of strings have been treated, the only strings that are
 * still placeholders are those for whom no word exists, thus replace those
 * with an arbitrary string.
 * 
 * @param pattern1: A pattern is phrase with words and placeholders. 
 * @param pattern2 A pattern is phrase with words and placeholders. 
 * @return phrase_t: A phrase matching both, or empty phrase if no solution. 
 */
phrase_t find_phrase(phrase_t& pattern1, phrase_t& pattern2){
    phrase_t no_solution {};
    if(pattern1.size() != pattern2.size()){return no_solution;}

    std::unordered_map<std::string, std::string> placeholder_map1;
    std::unordered_map<std::string, std::string> placeholder_map2;

    auto is_placeholder = [] (std::string& w) {
        return w.at(0) == '<' && w.at(w.size()-1) == '>';
    };

    bool all_placeholders_mapped {false};
    while(!all_placeholders_mapped){
        all_placeholders_mapped = true;
        std::string w1, w2;
        for(std::size_t i {0}; i < pattern1.size(); i++){
            w1 = pattern1[i];
            w2 = pattern2[i];

            if(!is_placeholder(w1) && !is_placeholder(w2)){
                if(w1 != w2){return no_solution;}
            } else if(is_placeholder(w1) && !is_placeholder(w2)){
                if(placeholder_map1.contains(w1)){
                    if(placeholder_map1.at(w1) != w2){
                        return no_solution;
                    } else{
                        pattern1.at(i) = w2;
                    }
                } else{
                    pattern1.at(i) = w2;
                    placeholder_map1[w1] = w2;
                    all_placeholders_mapped = false;
                    break;
                }
            } else if(!is_placeholder(w1) && is_placeholder(w2)){
                if(placeholder_map2.contains(w2)){
                    if(placeholder_map2.at(w2) != w1){
                        return no_solution;
                    } else{
                        pattern2.at(i) = w1;
                    }
                } else{
                    pattern2.at(i) = w1;
                    placeholder_map2[w2] = w1;
                    all_placeholders_mapped = false;
                    break;
                }
            } else if(placeholder_map1.contains(w1) && 
                      !placeholder_map2.contains(w2)){
                pattern1.at(i) = placeholder_map1.at(w1);
                pattern2.at(i) = placeholder_map1.at(w1);
                placeholder_map2[w2] = placeholder_map1.at(w1);
                all_placeholders_mapped = false;
                break;
            } else if(!placeholder_map1.contains(w1) && 
                      placeholder_map2.contains(w2)){
                pattern1.at(i) = placeholder_map2.at(w2);
                pattern2.at(i) = placeholder_map2.at(w2);
                placeholder_map1[w1] = placeholder_map2.at(w2);
                all_placeholders_mapped = false;
                break;
            } else if(placeholder_map1.contains(w1) && 
                      placeholder_map2.contains(w2)){
                if(placeholder_map1.at(w1) != placeholder_map2.at(w2)){
                    return no_solution;
                } else{
                    pattern1.at(i) = placeholder_map1.at(w1);
                    pattern2.at(i) = placeholder_map2.at(w2);
                }
            } else{
                continue;
            }
        }
    }

    std::string w1, w2;
    for(std::size_t i {0}; i < pattern1.size(); i++){
        w1 = pattern1.at(i);
        w2 = pattern2.at(i);
        if(is_placeholder(w1) && is_placeholder(w2)){
            pattern1.at(i) = "a";
            pattern2.at(i) = "a";
        }
    }
    
    return pattern1;
}

/**
 * @brief Prints a given phrase, or prints `-` if phrase is empty.
 * 
 * @param phrase: vector of strings. 
 */
void print_phrase(const phrase_t& phrase){
    if(phrase.size() > 0){
        std::ranges::copy(phrase, 
                          std::ostream_iterator<std::string>(std::cout, " "));
    }
    else{
        std::cout << "-";
    }

    std::cout << "\n";
}

// ============== END OF FILE ==============

