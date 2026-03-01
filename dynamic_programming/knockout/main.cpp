/**
* main.cpp
 * -----------------
 * Knockout Tournament (https://open.kattis.com/problems/knockout):
 *  Given a number of players and the freedom to arrange them initially
 *  to play a tournament, what is the maximum probability of a specific
 *  player to win the tournament.
 *
 * Solution:
 *  Using dynamic programming, the probability of winning is computed using
 *  total and conditional probabilities. If the number of players is
 *  not being a power of 2, then use dummy players of no skills to play the
 *  weaker players.
 *
 **/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <unordered_map>
#include <vector>

using prob_map_t = std::unordered_map<std::string, double>;

double compute_win_prob(int player, int n_players, std::vector<int>& ratings);
double helper(std::vector<int>& complete_ratings, prob_map_t& probs_map,
              int player, int round, int lower, int upper);
std::string make_key(int player, int round);

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n_players;
    std::cin >> n_players;
    std::vector<int> ratings (n_players);
    for (int i = 0; i < n_players; ++i) {std::cin >> ratings[i];}

    std::cout << std::fixed << compute_win_prob(0, n_players, ratings)
              << std::setprecision(7) << '\n';
    return 0;
}

/**
 * Compute the maximum probability of `player` winning the tournament.
 * @param player: A specific player.
 * @param n_players: Number of players in the tournament.
 * @param ratings: List of numeric skill of each player.
 * @return Probability of winning the tournament.
 */
double compute_win_prob(const int player, const int n_players, std::vector<int>& ratings) {
    std::ranges::sort(ratings.begin() + 1, ratings.end());
    prob_map_t probs_map {}; // map["pr"] = win prob of player p at round r.
    int n_rounds {static_cast<int>(std::log2(n_players))};
    const int n_complete_players = (std::pow(2, n_rounds) == n_players)
        ? n_players : static_cast<int>(std::pow(2, n_rounds+1));
    int n_players_to_advance {n_complete_players - n_players};

    // Adding dummy players at strategic places to increase the chances
    // of winning of the specific player.
    std::vector<int> complete_ratings (n_complete_players);
    if (n_complete_players > n_players) {
        n_rounds++;
        int j {0};
        for (int i {0}; i < n_players; ++i) {
            complete_ratings[j] = ratings[i];
            if (n_players_to_advance != 0) {
                complete_ratings[j+1] = 0;
                j += 2;
                n_players_to_advance--;
            } else {j++;}
        }
    } else {
        complete_ratings = ratings;
    }

    // Compute the probability recursively using a helper function.
    const double player_prob {helper(complete_ratings, probs_map, player,
                                     n_rounds, 0, n_complete_players)};

    return player_prob;
}

/**
 * Recursive helper function to find and compute the probability for a player.
 * @param complete_ratings: List of numeric skills of players, inc. dummies.
 * @param probs_map: A memo for the probability of players reaching some round.
 * @param player: The player in question.
 * @param round: A round in the tournament.
 * @param lower: Lower limit for diving the players into two groups.
 * @param upper Upper limit for diving the players into two groups.
 * @return Probability of winning the tournament.
 */
double helper(std::vector<int>& complete_ratings, prob_map_t& probs_map,
              const int player, const int round, const int lower, const int upper) {
    // base case
    if (round == 0) return 1.0;

    // Computing the lower and upper limits for which players one
    // may play at the current round and which players one may
    // have played in the previous round.
    // Opponent limits: opponents of current round.
    // Group limits: opponents of previous round.
    const int mid {static_cast<int>(std::ceil((upper - lower) / 2))};
    int opp_lim_a, opp_lim_b, grp_lim_a, grp_lim_b;
    if (player < lower + mid) {
        opp_lim_a = lower+mid; opp_lim_b = upper;
        grp_lim_a = lower; grp_lim_b = lower+mid;
    } else {
        opp_lim_a = lower; opp_lim_b = lower+mid;
        grp_lim_a = lower+mid; grp_lim_b = upper;
    }

    // Find probability of `player` reaching the current round.
    const int rate_a {complete_ratings[player]};
    if (rate_a == 0) return 0; // dummy players
    double prob_a;
    const std::string player_key {make_key(player, round-1)};
    if (probs_map.contains(player_key)) {
        prob_a = probs_map.at(player_key);
    } else {
        prob_a = helper(complete_ratings, probs_map, player, round-1, grp_lim_a, grp_lim_b);
        probs_map[player_key] = prob_a;
    }

    // Compute the conditional probability of `player` winning the current round.
    double cond_prob {0.0};
    for (int opp {opp_lim_a}; opp < opp_lim_b; ++opp) {
        const std::string key_opp {make_key(opp, round-1)};
        const int rate_opp {complete_ratings[opp]};
        double prob_opp;
        if (probs_map.contains(key_opp)) {prob_opp = probs_map.at(key_opp);}
        else if (opp == 0) {prob_opp = 0.0;}
        else {
            prob_opp = helper(complete_ratings, probs_map, opp, round-1, opp_lim_a, opp_lim_b);
            probs_map[key_opp] = prob_opp;
        }
        cond_prob += (static_cast<double>(rate_a)/(rate_a + rate_opp) * prob_opp);
    }
    const double prob = cond_prob * prob_a;
    return prob;
}

/**
 * Create a key for the memo using a player and a round.
 * @param player: Some player.
 * @param round: Some round.
 * @return String concat of player and round. Ex: "12", for player 1 at round 2.
 */
std::string make_key(const int player, const int round) {
    return std::to_string(player) + std::to_string(round);
}

// ============== END OF FILE ==============

