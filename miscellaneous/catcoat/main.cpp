/*
 * main.cpp
 * --------
 * Cat Coat Colors (https://open.kattis.com/problems/catcoat):
 *  Given the colors of two parents, generate their offspring colors and their
 *  probabilities of occurring, according to a set of rules.
 *
 * Solution:
 *  The idea is to generate the probabilities of each gene occurring, then for
 *  each position in the solution code and each gene for that position
 *  recursively, construct a code, extract the corresponding color, and
 *  update that color's probability.
 */

#include <algorithm>
#include <iostream>
#include <print>
#include <unordered_map>
#include <string>
#include <tuple>
#include <vector>

using gene_prob_t = std::tuple<char, double>;
using gene_prob_dict_t = std::unordered_map<char, double>;
using color_prob_t = std::pair<std::string, double>;

std::vector<color_prob_t> generate_offspring_colors(
    const std::string &female_color, const std::string &male_color
);

gene_prob_dict_t get_gene_probabilities(const std::string &color);

std::unordered_map<std::string, std::string> COLOR_CODE_DICT = {
    {"Black", "B-D-"},
    {"Blue", "B-dd"},
    {"Chocolate", "bbD-"},
    {"Lilac", "bbdd"},
    {"Red", "D-O"}, 
    {"Cream", "ddO"}, 
    {"Black-Red Tortie", "B-D-Oo"}, 
    {"Blue-Cream Tortie", "B-ddOo"}, 
    {"Chocolate-Red Tortie", "bbD-Oo"}, 
    {"Lilac-Cream Tortie", "bbddOo"}
};

std::unordered_map<std::string, std::string> CODE_COLOR_DICT = {
    {"B-D-", "Black"},
    {"B-dd", "Blue"},
    {"bbD-", "Chocolate"},
    {"bbdd", "Lilac"},
    {"D-O", "Red"},
    {"D-OO", "Red"},
    {"ddO", "Cream"}, 
    {"ddOO", "Cream"}, 
    {"B-D-Oo", "Black-Red Tortie"},
    {"B-ddOo", "Blue-Cream Tortie"},
    {"bbD-Oo", "Chocolate-Red Tortie"},
    {"bbddOo", "Lilac-Cream Tortie"}
};

std::vector<std::string> BLACK_COLORS = {
    "Black", "Blue", "Chocolate", "Lilac"
};
std::vector<std::string> RED_COLORS = {"Red", "Cream"};
std::vector<std::string> MIXED_COLORS = {
    "Black-Red Tortie", "Blue-Cream Tortie", 
    "Chocolate-Red Tortie", "Lilac-Cream Tortie"
};

/**
 * Read input, generate probable offspring colors and print them.
 */
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string female_color;
    std::string male_color;
    while (std::getline(std::cin, female_color),
           std::getline(std::cin, male_color)) {

        std::vector<color_prob_t> probable_offspring_colors =
        generate_offspring_colors(female_color, male_color);

        for (const color_prob_t &t : probable_offspring_colors) {
            const auto [color, prob] = t;
            if (prob > 0.0) {
                std::println("{} {:.9f}", color, prob);
            }
        }
    }

    return 0;
}

/**
 * Given colors of two cats, generate their offspring colors and probabilities.
 *
 * @param female_color: color of the female parent
 * @param male_color: color of the male parent
 * @return List of (color, prob) pairs sorted by prob (desc) and alphabet (asc).
 */
std::vector<color_prob_t> generate_offspring_colors(
    const std::string &female_color, const std::string &male_color
){
    std::unordered_map<std::string, double> color_probs_dict = {
        {"Black", 0},
        {"Blue", 0},
        {"Chocolate", 0},
        {"Lilac", 0},
        {"Red", 0},
        {"Cream", 0},
        {"Black-Red Tortie", 0},
        {"Blue-Cream Tortie", 0},
        {"Chocolate-Red Tortie", 0},
        {"Lilac-Cream Tortie", 0}
    };

    const gene_prob_dict_t female_gene_probs =
        get_gene_probabilities(female_color);
    const gene_prob_dict_t male_gene_probs =
        get_gene_probabilities(male_color);

    constexpr int N_CODE_POSITIONS {6};

    char solution[N_CODE_POSITIONS] {'X', 'X', 'X', 'X', 'X', 'X'};

    // implements the backtracking algorithm to recursively try all possible
    // combinations of codes.
    auto backtracking = [&](this auto &self, const int pos, const double prob)
    -> void{
        if(pos == N_CODE_POSITIONS){
            std::string offspring_code_female, offspring_code_male;

            const std::string part1 = solution[0] == 'b' && solution[1] == 'b' ?
                "bb" : "B-";
            const std::string part2 = solution[2] == 'd' && solution[3] == 'd' ?
                "dd" : "D-";

            if(solution[4] == 'o' && solution[5] == 'o'){
                offspring_code_female = part1 + part2;
                offspring_code_male = part1 + part2;
            } else if((solution[4] == 'O' && solution[5] == 'o')){
                offspring_code_female = part1 + part2 + "Oo";
                offspring_code_male = part2 + "O";
            } else if (solution[4] == 'o' && solution[5] == 'O') {
                offspring_code_female = part1 + part2 + "Oo";
                offspring_code_male = part1 + part2;
            } else{
                offspring_code_female = part2 + "OO";
                offspring_code_male = part2 + "O";
            }

            const std::string& offspring_color_female = CODE_COLOR_DICT.at(
                offspring_code_female);
            const std::string& offspring_color_male = CODE_COLOR_DICT.at(
                offspring_code_male);

            color_probs_dict.at(offspring_color_female) += 0.5 * prob;
            color_probs_dict.at(offspring_color_male) += 0.5 * prob;

            return;
        }

        const char dominant = pos < 2 ? 'B' : pos < 4 ? 'D' : 'O';
        const char recessive = pos < 2 ? 'b' : pos < 4 ? 'd' : 'o';
        double dominant_prob, recessive_prob;

        if(pos % 2 == 0){
            // female
            dominant_prob = female_gene_probs.at(dominant) * prob;
            if (dominant_prob > 0.0) {
                solution[pos] = dominant;
                self(pos + 1, dominant_prob);
            }

            recessive_prob = female_gene_probs.at(recessive) * prob;
            if (recessive_prob > 0.0) {
                solution[pos] = recessive;
                self(pos+1, recessive_prob);
            }
            solution[pos] = 'X'; // undo last step
        } else{
            // male
            dominant_prob = male_gene_probs.at(dominant) * prob;
            if (dominant_prob > 0.0) {
                solution[pos] = dominant;
                self( pos+1, dominant_prob);
            }

            recessive_prob = male_gene_probs.at(recessive) * prob;
            if (recessive_prob > 0.0) {
                solution[pos] = recessive;
                self(pos+1, recessive_prob);
            }
            solution[pos] = 'X';
        }
    };

    backtracking(0, 1.0);

    std::vector<color_prob_t> probable_colors {
        color_probs_dict.begin(), color_probs_dict.end()
    };

    std::ranges::sort(
        probable_colors,
        [](const color_prob_t& t1, const color_prob_t& t2) -> bool {
            return (t1.second == t2.second) ?
                t1.first < t2.first : t1.second > t2.second;
        });

    return probable_colors;
}

/**
 * Given a color return a table of each gene and their probability of
 * being passed down to an offspring.
 * @param color: Color of a cat.
 * @return: Table of (gene, prob) pairs.
 */
gene_prob_dict_t get_gene_probabilities(const std::string &color){
    gene_prob_dict_t gene_probs_dict {
            {
                {'B', 0.0}, {'b', 0.0},
                {'D', 0.0}, {'d', 0.0},
                {'O', 0.0}, {'o', 0.0}
            }
    };

    const std::string& color_code {COLOR_CODE_DICT.at(color)};
    
    if(std::ranges::contains(MIXED_COLORS, color) || 
       std::ranges::contains(BLACK_COLORS, color)){
        if(color_code.contains("B-")){
            gene_probs_dict.at('B') = 0.75;
            gene_probs_dict.at('b') = 0.25;
        } else{
            gene_probs_dict.at('b') = 1.0;
        }
        
        if(color_code.contains("D-")){
            gene_probs_dict.at('D') = 0.75;
            gene_probs_dict.at('d') = 0.25;
        } else{
            gene_probs_dict.at('d') = 1.0;
        }

        if(std::ranges::contains(MIXED_COLORS, color)){
            gene_probs_dict.at('O') = 0.5;
            gene_probs_dict.at('o') = 0.5;
        } else{
            gene_probs_dict.at('o') = 1.0;
        }

    } else{
        gene_probs_dict.at('B') = 0.5;
        gene_probs_dict.at('b') = 0.5;
    
        if(color_code.contains("D-")){
            gene_probs_dict.at('D') = 0.75;
            gene_probs_dict.at('d') = 0.25;
        } else{
            gene_probs_dict.at('d') = 1.0;
        }
        gene_probs_dict.at('O') = 1.0;
    }
    return gene_probs_dict;
}

// ============== END OF FILE ==============