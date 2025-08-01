/**
* main.cpp
 * -----------------
 * MeTube (https://open.kattis.com/problems/dutub):
 *  Given a list of videos each having a length and a set of categories it
 *  belongs to, which of the videos should one select to watch inorder to
 *  watch all categories in the shortest time?
 *
 * Solution:
 *  This problem can be solved using dynamic programming. For each video,
 *  either watch it or not. Once a decision is made for a video, check the
 *  result for the remaining videos and categories.
 *
 **/

#include <algorithm>
#include <iostream>
#include <print>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>



struct Video {
    const int length;
    const std::string categories;
};

using videos_t = std::vector<Video>;
using categories_t = std::unordered_set<char>;
using memo_t = std::unordered_map<std::string, std::pair<int, int>>;

constexpr int LARGE_NUM {30 * 900};

int min_watching_time(
        categories_t categories, int n_videos, videos_t& videos, memo_t& memo
    );

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n_videos;
    while (std::cin >> n_videos) {
        int length;
        std::string video_categories;
        categories_t categories;
        videos_t videos;
        memo_t memo;

        for (int i = 0; i < n_videos; i++) {
            std::cin >> length;
            std::cin >> video_categories;
            videos.push_back({length, video_categories});
            categories.insert(video_categories.begin(), video_categories.end());
        }

        int min_time {min_watching_time(categories, n_videos, videos, memo)};
        std::println("{0}", min_time);
    }

    return 0;
}

/**
 * @brief Find and return the shortest time needed to watch all categories.
 *
 * @param categories: Set of all categories not seen.
 * @param n_videos: Number of videos not watched.
 * @param videos: List of all videos.
 * @param memo: Cache of previously computed results.
 * @return min_time: the time needed to watch videos in all categories.
 */
int min_watching_time(
    categories_t categories, int n_videos, videos_t& videos, memo_t& memo
    ) {
    int min_time {0};
    std::string key (categories.begin(), categories.end());
    std::ranges::sort(key);

    if (categories.empty()) {return 0;}
    if (memo.contains(key)) {
        if (const auto& [length, n_vid] = memo[key]; n_videos <= n_vid)
            {return length;}
    }
    if (n_videos == 0) {return LARGE_NUM;}

    categories_t subcategories;
    const auto&[length, video_categories] {videos.at(n_videos - 1)};

    for (const char& c : categories) {
        if (!video_categories.contains(c)) {subcategories.insert(c);}
    }

    int watch_value;
    if (subcategories.size() < categories.size()) {
        watch_value =
            length + min_watching_time(subcategories, n_videos - 1, videos, memo);
    } else {watch_value = LARGE_NUM;}

    int not_watch_value {
        min_watching_time(categories, n_videos - 1, videos, memo)
    };

    if (watch_value < not_watch_value) {
        memo[key] = {watch_value, n_videos};
        min_time = watch_value;
    } else {
        memo[key] = {not_watch_value, n_videos - 1};
        min_time = not_watch_value;
    }
    return min_time;
}

// ============== END OF FILE ==============

