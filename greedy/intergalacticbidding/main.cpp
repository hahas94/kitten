/**
* main.cpp
 * -----------------
 * intergalactic bidding (https://open.kattis.com/problems/intergalacticbidding):
 *
 *  Given a set of large integers such that each one is at least twice as
 *  the previous one, and given a sum, find the integers that together make
 *  up the sum.
 *
 * Solution:
 *  Due to the nature of the problem, only one set of integers can make up
 *  the sum, hence we need to find this set only once. Each integer is either
 *  included in that sum or not. The idea is to select the integers in order,
 *  where for each of the remaining integers, we select the one that together
 *  with the currently selected ones drives the difference between the target
 *  sum and current sum to zero. The selection of later integers is based
 *  on the principle of maximum contribution, that's selecting the one
 *  integer contributing the most to reduce the difference. This integer is
 *  found using an ad-hoc variant of binary search.
 *
 **/

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

#include <big_integer.hpp>

using names_set_t = std::unordered_set<std::string>;

struct Person {
    std::string name {};
    BigInteger bid {"0"};
};

using bidders_t = std::vector<Person>;

names_set_t find_winners(const bidders_t& bidders_c, const BigInteger& sum, int n_bidders);

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::string s, bid_str, name;
    while (std::cin >> n >> s) {
        bidders_t bidders (n);
        BigInteger sum {s};
        for (int i = 0; i < n; i++) {
            std::cin >> name >> bid_str;
            bidders[i] = {name, BigInteger{bid_str}};
        }

        names_set_t winners {find_winners(bidders, sum, n)};
        std::cout << winners.size() << std::endl;
        std::ranges::copy(winners, std::ostream_iterator<std::string>(std::cout, "\n"));
    }

    return 0;
}

names_set_t find_winners(const bidders_t& bidders_c, const BigInteger& sum, const int n_bidders) {
    BigInteger bigint_zero {"0"};
    bidders_t bidders (bidders_c);
    std::ranges::sort(bidders, [](const Person& p1, const Person& p2) {
        return p1.bid < p2.bid;
    });
    const BigInteger bids_sum {std::accumulate(
        bidders.begin(),
        bidders.end(),
        bigint_zero,
        [](const BigInteger& s, const Person& p) {return s + p.bid;})
        + BigInteger{"1"}
    };

    names_set_t winners;
    if (sum >= bids_sum) return winners;
    Person LARGE_BIDDER {"LB", bids_sum};
    BigInteger diff {"0"};

    // For each person, find the group of bidders that they together
    // make up the sum.
    for (int i {0}; i < n_bidders; i++) {
        auto& [name, bid] {bidders[i]};
        diff = sum - bid;
        if (diff.is_negative()) break; // sum is impossible to construct.
        winners.insert(name);

        // Get diff closer and closer towards 0 by selecting appropriate bidders.
        int lower {i+1}, upper {n_bidders-1};
        while (diff > bigint_zero) {
            BigInteger sub = LARGE_BIDDER.bid;
            int pos {upper};
            std::string name_tmp;
            while (pos <= upper && pos >= lower) {
                auto& [name, bid] = bidders[pos];
                name_tmp = name;
                if (winners.contains(name)) {
                    upper = pos - 1;
                    pos--;
                }
                sub = diff - bid;

                // Performing a variant of binary search to find
                // the fittest bidder.
                if (pos == upper && !sub.is_negative()) {
                    lower = i + 1;
                    upper--;

                } else if (!sub.is_negative()) {
                    lower = pos;
                    pos = upper;
                } else {
                    upper = pos - 1;
                    if (int new_pos {(pos + lower) / 2}; new_pos < pos) {
                        pos = new_pos;
                    } else {
                        lower = i+1;
                        pos = upper;
                    }
                }
            }
            if (sub == LARGE_BIDDER.bid) break;
            diff = sub;
            winners.insert(name_tmp);
        }
        if (diff == bigint_zero) break;
        winners.clear();
    }
    return winners;
}
// ============== END OF FILE ==============
