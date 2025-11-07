/*
 * DO NOT MAKE ANY CHANGES
 */

#include "gtest/gtest.h"
#include "problem_1/LRU.hpp"

TEST(problem_1, LRU_put_get) {
    int evicted_value;
    LRUCache<int> lru(5);
    std::vector<std::pair<std::string, int>> test_cases = {
            {"a", 1},
            {"b", 2},
            {"c", 3},
            {"d", 4},
            {"e", 5},
    };
    for (auto &test_case: test_cases) {
        bool evicted_item = lru.put(test_case.first, test_case.second, evicted_value);
        ASSERT_FALSE(evicted_item);
    }

    for (auto &test_case: test_cases) {
        int actual;
        bool found = lru.get(test_case.first, actual);
        ASSERT_TRUE(found);
        ASSERT_EQ(test_case.second, actual);
    }
}

TEST(problem_1, eviction_least_recently_used) {
    int evicted_value;
    LRUCache<int> lru(4);
    std::vector<std::pair<std::string, int>> test_cases = {
            {"a", 1},
            {"b", 2},
            {"c", 3},
            {"d", 4},
            {"e", 5},
            {"f", 6},
            {"g", 7},
            {"h", 8},
    };

    /*
     * put items to lru to the limit (4)
     */
    int half = (int) test_cases.size() / 2;
    for (int i = 0; i < half; ++i) {
        auto test_case = test_cases[i];
        lru.put(test_case.first, test_case.second, evicted_value);
    }

    /*
     * put 4 more items, and check for eviction
     * before pushing one element:  vector [5, 6, 7, 8] => lru {4, 3, 2, 1}
     * after pushing one element:   vector [6, 7, 8] => lru {5, 4, 3, 2} evicted 1
     */
    std::vector<std::pair<std::string, int>> items_in_lru(test_cases.begin(), test_cases.begin() + half);
    std::reverse(items_in_lru.begin(), items_in_lru.end());

    // items_in_lru here is {4, 3, 2, 1}
    // Each time, the data at the end of items_in_lru will be evicted. 1 goes first, and then 2, etc.

    for (int i = 0; i < half; ++i) {
        auto test_case = test_cases[half + i];
        bool evicted_item = lru.put(test_case.first, test_case.second, evicted_value);

        // Verify:
        // 1. Eviction happens
        // 2. The right item was evicted
        // 3. The evicted item does not exist in the lru
        ASSERT_TRUE(evicted_item);
        ASSERT_EQ(test_cases[i].second, evicted_value);
        auto found = lru.get(items_in_lru.back().first, evicted_value);
        ASSERT_FALSE(found);

        // Verify lru has all what it should have
        items_in_lru.pop_back();
        items_in_lru.insert(items_in_lru.begin(), test_cases[half + i]);
        for (auto &item: items_in_lru) {
            int actual;
            found = lru.get(item.first, actual);
            ASSERT_TRUE(found);
            ASSERT_EQ(item.second, actual);
        }
    }
}

TEST(problem_1, LRU_non_existant_item) {
    LRUCache<int> lru(5);
    int actual;
    bool found = lru.get("xyz", actual);
    ASSERT_FALSE(found);

    int evicted_value;
    lru.put("abc", 30, evicted_value);
    found = lru.get("xyz", actual);
    ASSERT_FALSE(found);
}

