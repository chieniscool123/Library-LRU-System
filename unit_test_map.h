/*
 * DO NOT MAKE ANY CHANGES
 */

#pragma once

#include "problem_1/array_map.h"
#include "unit_test_map.h"
#include "gtest/gtest.h"

std::string case_id(int id) {
    return "case " + std::to_string(id) + " failed.";
}

std::string case_id(int id1, int id2) {
    return "case (" + std::to_string(id1) + ", " + std::to_string(id2) + ") failed.";
}

//#define PRINT

template<typename KEY_TYPE, typename VAL_TYPE>
void array_map_put_new_key() {
    int SIZE = 5;
    ArrayMap<KEY_TYPE, VAL_TYPE> hash_map(SIZE);
    // verifying putting new key
    for (int i = 0; i < SIZE * 3; i++) {
        VAL_TYPE expect = (VAL_TYPE) i * 2;
        hash_map.put(i, expect);
        ASSERT_EQ(hash_map.size(), i + 1);
        VAL_TYPE actual;
        hash_map.get(i, actual);
        ASSERT_TRUE(expect == actual);
    }
    int current_size = hash_map.size();

    // verifying putting existing key
    for (int i = 0; i < SIZE * 3; i++) {
        VAL_TYPE expect = (VAL_TYPE) i * 3;
        hash_map.put(i, expect);
    }
    ASSERT_EQ(current_size, hash_map.size());

    for (int i = 0; i < SIZE * 3; i++) {
        VAL_TYPE expect = (VAL_TYPE) i * 3;
        VAL_TYPE actual;
        hash_map.get(i, actual);
        ASSERT_TRUE(expect == actual);
    }

#ifdef PRINT
    hash_map.print();
#endif
}

template<typename KEY_TYPE, typename VAL_TYPE>
void verify_remove(ArrayMap<KEY_TYPE, VAL_TYPE> &hash_map, int expect_size, int to_remove) {
    hash_map.remove(to_remove);
    VAL_TYPE val;
    ASSERT_FALSE(hash_map.get(to_remove, val));
    ASSERT_EQ(expect_size, hash_map.size());
}

template<typename KEY_TYPE, typename VAL_TYPE>
void array_map_test_remove() {
    int SIZE = 100;
    ArrayMap<KEY_TYPE, VAL_TYPE> hash_map;

    // fill array
    for (int i = 0; i < SIZE; i++) {
        hash_map.put(i, i * 2);
    }
    for (int i = 0; i < SIZE; i++) {
        VAL_TYPE val;
        hash_map.get(i, val);
        ASSERT_EQ(i * 2, val);

        // remove the value
        verify_remove(hash_map, SIZE - i - 1, i);

        // remove the same value again, should be no-op
        verify_remove(hash_map, SIZE - i - 1, i);
    }
    ASSERT_EQ(0, hash_map.size());

    // another round to remove from an empty map
    for (int i = 0; i < SIZE; i++) {
        // remove the value
        verify_remove(hash_map, 0, i);
    }
}

template<typename KEY_TYPE, typename VAL_TYPE>
class TestCaseMapEqual {
public:
    std::vector<std::pair<KEY_TYPE, VAL_TYPE>> map_1_data;
    std::vector<std::pair<KEY_TYPE, VAL_TYPE>> map_2_data;
    bool should_equal;

    TestCaseMapEqual(const std::vector<std::pair<KEY_TYPE, VAL_TYPE>> &map1Data,
                     const std::vector<std::pair<KEY_TYPE, VAL_TYPE>> &map2Data, bool should_equal) : map_1_data(
            map1Data), map_2_data(map2Data), should_equal(should_equal) {}

};

template<typename KEY_TYPE, typename VAL_TYPE>
void array_map_test_equal() {
    std::vector<TestCaseMapEqual<KEY_TYPE, VAL_TYPE>> test_cases = {
            TestCaseMapEqual<KEY_TYPE, VAL_TYPE>(
                    {},
                    {},
                    true),
            TestCaseMapEqual<KEY_TYPE, VAL_TYPE>(
                    {},
                    {{1, 3},},
                    false),
            TestCaseMapEqual<KEY_TYPE, VAL_TYPE>(
                    {{1, 3}},
                    {},
                    false),
            TestCaseMapEqual<KEY_TYPE, VAL_TYPE>(
                    {{1, 3},},
                    {{1, 3},},
                    true),
            TestCaseMapEqual<KEY_TYPE, VAL_TYPE>(
                    {{1, 3},
                     {6, 2}},
                    {{1, 3},},
                    false),
            TestCaseMapEqual<KEY_TYPE, VAL_TYPE>(
                    {
                            {1, 3},
                            {6, 2}
                    },
                    {
                            {6, 2},
                            {1, 3}
                    },
                    true),
            TestCaseMapEqual<KEY_TYPE, VAL_TYPE>(
                    {
                            {1, 3},
                            {9, 10},
                            {6, 2}
                    },
                    {
                            {6, 2},
                            {1, 3},
                            {9, 10}
                    },
                    true),
            TestCaseMapEqual<KEY_TYPE, VAL_TYPE>(
                    {
                            {1, 3},
                            {9, 10},
                            {6, 2}
                    },
                    {
                            {6, 2},
                            {1, 3},
                            {9, 8}
                    },
                    false),
    };

    for (int i = 0; i < test_cases.size(); i++) {
        auto &test_case = test_cases[i];
        ArrayMap<KEY_TYPE, VAL_TYPE> map_1(test_case.map_1_data);
        ArrayMap<KEY_TYPE, VAL_TYPE> map_2(test_case.map_2_data);
        ASSERT_EQ(test_case.should_equal, map_1 == map_2) << case_id(i);
        ASSERT_EQ(test_case.should_equal, map_2 == map_1) << case_id(i);
        ASSERT_EQ(!test_case.should_equal, map_1 != map_2) << case_id(i);
        ASSERT_EQ(!test_case.should_equal, map_2 != map_1) << case_id(i);
    }
}
