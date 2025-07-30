/**
* main.cpp
 * -----------------
 * Basic Interpreter (https://open.kattis.com/problems/basicinterpreter):
 *  The task is to develop an interpreter for a dialect of a language,
 *  where a program in the language has a strict format.
 *
 * Solution:
 *  Essentially simulating the instructions, with extra attention to speed.
 *
 **/

#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <functional>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

const std::unordered_map<std::string, std::function<int(int, int)>>
    BINARY_OPERATORS {
        {"+", std::plus<>()},
        {"-", std::minus<>()},
        {"*", std::multiplies<>()},
        {"/", std::divides<>()}
    };

const std::unordered_map<std::string, std::function<bool(int, int)>>
    BINARY_COMPARATORS {
        {"=", std::equal_to<>()},
        {"<>", std::not_equal_to<>()},
        {">", std::greater<>()},
        {">=", std::greater_equal<>()},
        {"<", std::less<>()},
        {"<=", std::less_equal<>()}
    };

// A structure for a line of a program, where `tokens` is its tokenization.
struct Line {
    int label;
    std::string line;
    std::vector<std::string> tokens;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::unordered_map<std::string, int> variables_map;
    std::vector<Line> program;
    std::string line;
    int label;
    std::ostringstream os;

    while (std::cin >> label && std::getline(std::cin, line)) {
        std::istringstream iss(line);
        std::vector<std::string> tokens {
            std::istream_iterator<std::string>{iss},
            std::istream_iterator<std::string>{}
        };
        program.push_back({label, line, tokens});
    }

    auto get_value = [&](const std::string& token) -> int {
         return std::isupper(token[0]) ? variables_map[token] : std::stoi(token);
    };

    std::ranges::sort(program, [](const auto& line1, const auto& line2) {
        return line1.label < line2.label;
    });

    std::unordered_map<int, std::size_t> line_number_indices;
    for (std::size_t i {0}; i < program.size(); i++) {
        line_number_indices[program[i].label] = i;
    }

    std::size_t index {0};

    while (index < program.size()) {
        line = program[index].line;
        auto tokens = program[index].tokens;

        if (std::string& first_token {tokens.at(0)}; first_token == "LET") {
            variables_map[tokens.at(1)] = tokens.size() == 4 ?
                get_value(tokens.at(3)) :
                BINARY_OPERATORS.at(tokens.at(4))(
                    get_value(tokens.at(3)), get_value(tokens.at(5)));
        } else if (first_token == "IF") {
            // ex. IF A < 2 THEN GOTO 12
            bool cond_is_true = BINARY_COMPARATORS.at(tokens.at(2))(
                get_value(tokens.at(1)), get_value(tokens.at(3))
                );
            if (cond_is_true) {
                index = line_number_indices[std::stoi(tokens.at(6))];
                continue;
            }
        } else if (first_token == "PRINT") {
            std::string& to_print {tokens.at(1)};
            to_print.at(0) == '"' ?
                os << line.substr(8, line.length() - 8 - 1) :
                os << variables_map[to_print];
        } else {
            std::string& to_print {tokens.at(1)};
           to_print.at(0) == '"' ?
                os << line.substr(10, line.length() - 10 - 1) << "\n" :
                os << variables_map[to_print] << "\n";
        }
        index++;
    }
    std::cout << os.str();
    return 0;
}

// ============== END OF FILE ==============

