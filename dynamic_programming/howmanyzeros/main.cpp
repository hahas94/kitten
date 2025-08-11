/**
* main.cpp
 * -----------------
 * How many 0's? (https://open.kattis.com/problems/howmanyzeros):
 *  Given a range of numbers between [L, R], find the number of times
 *  the digit 0 appears.
 *
 * Solution:
 *  Using dynamic programming, we can build a number digit by digit and keeping
 *  track of the number of times 0 has been seen, while respecting constraints
 *  such as not considering numbers larger than the original, or counting
 *  invalid 0's.
 *
 **/
 
#include <algorithm>
#include <cstring>
#include <iostream>
#include <print>
#include <string>
#include <sstream>
#include <vector>

using ll_t = long long int;
using digits_t = std::vector<int>;

digits_t make_digits(ll_t number);

ll_t count(const digits_t& digits, std::size_t digit_pos, int cnt,
           bool is_leading_zero, bool is_bounded);

ll_t memo[18][18][2][2]; // memo[position][count][is_leading_zero][is_bounded]

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    ll_t a;
    ll_t b;
    std::ostringstream oss;

    while (std::cin >> a >> b) {
        if (a != -1 && b != -1) {
            digits_t digits_a {make_digits(a - 1)};
            digits_t digits_b {make_digits(b)};

            std::memset(memo, -1, sizeof(memo));
            const ll_t result_a = (a == 0) ? 0 :
                count(digits_a, 0, 0, true, true);
            std::memset(memo, -1, sizeof(memo));
            const ll_t result_b = count(digits_b, 0, 0, true, true);

            oss << result_b - result_a << "\n";
        }
    }

    std::cout << oss.str();
    return 0;
}

/**
 * Count the number of times 0 appears in a number, by recursively counting
 * appearances of it.
 * @param digits: Vector digits of the number, from left to right.
 * @param digit_pos: The position of the current digit to fill.
 * @param cnt: Count of times 0 has been seen.
 * @param is_leading_zero: Whether the number build so far starts with a zero.
 * @param is_bounded: Whether there is an upperbound on which digits to be used.
 * @return The count of 0's seen so far.
 */
ll_t count(const digits_t& digits, const std::size_t digit_pos, const int cnt,
           const bool is_leading_zero, const bool is_bounded) {

    if (digit_pos >= digits.size()) return cnt;
    const std::size_t pos = digits.size() - digit_pos - 1;
    if (memo[pos][cnt][is_leading_zero][is_bounded] != -1) \
        return memo[pos][cnt][is_leading_zero][is_bounded];

    const int upperbound {!is_bounded ? 9 : digits[digit_pos]};
    ll_t count_0 {0};

    for (int d {0}; d <= upperbound; ++d) {
        count_0 += count(digits, digit_pos + 1,
            cnt + (d == 0 && ((is_leading_zero && pos == 0) || !is_leading_zero)),
            d == 0 && is_leading_zero, is_bounded && d == digits[digit_pos]);
    }

    memo[pos][cnt][is_leading_zero][is_bounded] = count_0;

    return count_0;
}

/**
 * Turn a natural integer into a vector of its digits, with its leading digit
 * being first in the vector.
 *
 * @param number The number to digitize.
 * @return vector of digits,
 */
digits_t make_digits(const ll_t number) {
    digits_t digits;
    std::string num_str {std::to_string(number)};
    std::ranges::transform(num_str, std::back_inserter(digits),
                           [](const char c) {return c - '0';});

    return digits;
}
// ============== END OF FILE ==============

