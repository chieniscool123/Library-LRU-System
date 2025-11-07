/*
 * DO NOT MAKE ANY CHANGES
 */

#pragma once

#include "problem_1/array_list.h"

template<typename T>
void fill_list_with_vector(List<T> &list, const std::vector<T> &data) {
    for (T val: data) {
        list.push_back(val);
    }
}

template<typename T>
void fill_list_with_sequence(int n, List<T> &list) {
    for (int i = 0; i < n; i++) {
        list.push_back(i);
    }
}

template<typename T>
void test_new_array_list_size_capacity() {
    T *test_list = new T(5);
    ASSERT_EQ(0, test_list->size());
    ASSERT_EQ(5, test_list->capacity());
    delete test_list;
}

template<typename T>
void test_copy_constructor() {
    std::vector<std::vector<int>> test_cases = {
            {},
            {1},
            {1, 2},
            {1, 3, 3},
            {1, 3, 4},
    };

    T *plist;
    for (const std::vector<int> &test_case: test_cases) {
        T other_list(test_case.size());
        fill_list_with_sequence(test_case.size(), other_list);

        // check for value copied
        T list(other_list);
        ASSERT_TRUE(list == other_list);

        plist = new T(list);
        ASSERT_TRUE(*plist == list);
        delete plist;

        // check against shallow copy
        if (other_list.size() != 0) {
            other_list[0] = 99;
            ASSERT_TRUE(99 != list[0]);
        }
    }
}

template<typename T>
void test_push_back() {
    std::vector<std::vector<int>> test_cases = {
            {},
            {0},
            {0, 1},
            {0, 1, 2},
            {0, 1, 2, 3},
    };

    for (std::vector<int> test_case: test_cases) {
        size_t test_case_size = test_case.size();

        // create a new list and push test case numbers into it one by one
        T list(test_case_size);
        for (int i = 0; i < test_case_size; i++) {
            ASSERT_EQ(i, test_case[i]);
            list.push_back(test_case[i]);
            ASSERT_EQ(i + 1, list.size());
        }

        // push one more to go over the capacity
        ASSERT_NO_FATAL_FAILURE(list.push_back(99));

        // verify list has the right content
        ASSERT_EQ(test_case_size, list.size());
        for (int i = 0; i < test_case_size; i++) {
            ASSERT_EQ(list[i], test_case[i]);
        }
    }
}

template<typename T>
void test_push_front() {
    std::vector<std::vector<int>> test_cases = {
            {},
            {0},
            {1, 0},
            {2, 1, 0},
            {3, 2, 1, 0},
    };

    for (std::vector<int> test_case: test_cases) {
        size_t test_case_size = test_case.size();

        // create a new list and push test case numbers into it one by one
        T list(test_case_size);
        for (int i = 0; i < test_case_size; i++) {
            ASSERT_EQ(test_case_size - i - 1, test_case[i]);
            list.push_front(test_case[i]);
            ASSERT_EQ(i + 1, list.size());
        }

        // push one more to go over the capacity
        ASSERT_NO_FATAL_FAILURE(list.push_back(99));

        // verify list has the right content
        ASSERT_EQ(test_case_size, list.size());
        for (int i = 0; i < test_case_size; i++) {
            ASSERT_EQ(list[i], test_case[test_case_size - i - 1]);
        }
    }
}

template<typename T>
void test_pop_back() {
    const int TEST_SIZE = 5;
    for (int n = 0; n < TEST_SIZE; n++) {
        T list(n);

        // pop when list is newly created
        ASSERT_NO_FATAL_FAILURE(list.pop_back());
        ASSERT_EQ(0, list.size());

        // fill the list from 0 to n-1
        fill_list_with_sequence(n, list);

        // pop everything from the back of the list
        for (int i = 0; i < n; i++) {
            list.pop_back();
            ASSERT_EQ(n - i - 1, list.size());
            for (int j = 0; j < n - i - 1; j++) {
                ASSERT_EQ(j, list[j]);
            }
        }

        // pop one more time
        ASSERT_NO_FATAL_FAILURE(list.pop_back());
        ASSERT_EQ(0, list.size());
    }
}

template<typename T>
void test_pop_front() {
    const int TEST_SIZE = 5;
    for (int n = 0; n < TEST_SIZE; n++) {
        T list(n);

        // pop when list is newly created
        ASSERT_NO_FATAL_FAILURE(list.pop_front());
        ASSERT_EQ(0, list.size());

        // fill the list from 0 to n-1
        fill_list_with_sequence(n, list);

        // pop everything from the back of the list
        for (int i = 0; i < n; i++) {
            list.pop_front();
            ASSERT_EQ(n - i - 1, list.size());
            for (int j = 0; j < n - 1 - i; j++) {
                ASSERT_EQ(j + i + 1, list[j]);
            }
        }

        // pop one more time
        ASSERT_NO_FATAL_FAILURE(list.pop_front());
        ASSERT_EQ(0, list.size());
    }
}

template<class T>
class TestCaseForMerge {
public:
    std::vector<T> list_1_data;
    std::vector<T> list_2_data;
    std::vector<T> expect;

    TestCaseForMerge(const std::vector<T> &list_1_data, const std::vector<T> &list_2_data, const std::vector<T> &expect)
            : list_1_data(list_1_data), list_2_data(list_2_data), expect(expect) {}
};

template<typename T, typename K>
void run_merge_verify(std::vector<TestCaseForMerge<K>> test_cases) {
    for (const auto &test_case: test_cases) {
        // load list 1
        T list_1(test_case.list_1_data.size());
        fill_list_with_vector(list_1, test_case.list_1_data);

        ASSERT_EQ(test_case.list_1_data.size(), list_1.size());

        // load list 2 and its copy
        T list_2(test_case.list_2_data.size());
        fill_list_with_vector(list_2, test_case.list_2_data);
        T list_2_copy(list_2);

        ASSERT_EQ(test_case.list_2_data.size(), list_2.size());

        // load expect list
        T expect_list(test_case.expect.size());
        fill_list_with_vector(expect_list, test_case.expect);

        ASSERT_EQ(test_case.expect.size(), expect_list.size());

        // call merge
        list_1.merge(list_2);

        // verify elements merge correct
        ASSERT_TRUE(expect_list == list_1);

        // verify list2 is not changed
        ASSERT_TRUE(list_2 == list_2_copy);
    }
}

template<typename T>
void test_merge_int() {
    std::vector<TestCaseForMerge<int>> test_cases = {
            TestCaseForMerge<int>({1}, {}, {1}),
            TestCaseForMerge<int>({}, {1}, {1}),
            TestCaseForMerge<int>({1}, {2}, {1, 2}),
            TestCaseForMerge<int>({1, 2}, {3, 4}, {1, 2, 3, 4}),
            TestCaseForMerge<int>({1}, {3, 4}, {1, 3, 4}),
            TestCaseForMerge<int>({1, 2}, {4}, {1, 2, 4}),
            TestCaseForMerge<int>({1, 3}, {2, 4}, {1, 2, 3, 4}),
            TestCaseForMerge<int>({1, 5}, {2, 4}, {1, 2, 4, 5}),
            TestCaseForMerge<int>({-3, -3, -3}, {-3, -3}, {-3, -3, -3, -3, -3}),
            TestCaseForMerge<int>({1, 3, 5}, {2, 4}, {1, 2, 3, 4, 5}),
            TestCaseForMerge<int>({1, 3, 8}, {2, 4, 6}, {1, 2, 3, 4, 6, 8}),
    };
    run_merge_verify<T, int>(test_cases);
}

template<typename T>
void test_merge_string() {
    std::vector<TestCaseForMerge<std::string>> test_cases = {
            TestCaseForMerge<std::string>({}, {"b"}, {"b"}),
            TestCaseForMerge<std::string>({"a"}, {}, {"a"}),
            TestCaseForMerge<std::string>({"a"}, {"b"}, {"a", "b"}),
            TestCaseForMerge<std::string>({"b"}, {"a"}, {"a", "b"}),
            TestCaseForMerge<std::string>({"ab"}, {"ac"}, {"ab", "ac"}),
            TestCaseForMerge<std::string>({"ab", "ef"}, {"cd", "xy"}, {"ab", "cd", "ef", "xy"}),
    };
    run_merge_verify<T, std::string>(test_cases);
}

template<typename T>
void test_merge_float() {
    std::vector<TestCaseForMerge<float>> test_cases = {
            TestCaseForMerge<float>({}, {2.3}, {2.3}),
            TestCaseForMerge<float>({0.5}, {}, {0.5}),
            TestCaseForMerge<float>({0.5}, {2.3}, {0.5, 2.3}),
            TestCaseForMerge<float>({2.3}, {0.5}, {0.5, 2.3}),
            TestCaseForMerge<float>({1.1}, {3.9}, {1.1, 3.9}),
            TestCaseForMerge<float>({1.1, 8.7}, {4.51, 20.1}, {1.1, 4.51, 8.7, 20.1}),
    };
    run_merge_verify<T, float>(test_cases);
}

template<class T>
class TestCaseForRemove {
public:
    std::vector<T> list_data;
    T to_remove;
    std::vector<T> expect;

    TestCaseForRemove(const std::vector<T> &list_data, T to_remove, const std::vector<T> &expect) :
            list_data(list_data), to_remove(to_remove), expect(expect) {}
};

template<typename T, typename K>
void run_remove_verify(std::vector<TestCaseForRemove<K>> test_cases) {
    for (auto test_case: test_cases) {
        T list(test_case.list_data.size());
        fill_list_with_vector(list, test_case.list_data);
        ASSERT_EQ(test_case.list_data.size(), list.size());

        T expect_list(test_case.expect.size());
        fill_list_with_vector(expect_list, test_case.expect);
        ASSERT_EQ(test_case.expect.size(), expect_list.size());

        list.remove(test_case.to_remove);
        ASSERT_TRUE(list == expect_list);
    }
}

template<typename T, typename K>
void test_remove_primitive_number() {
    std::vector<TestCaseForRemove<K>> test_cases = {
            TestCaseForRemove<K>({1}, 2, {1}),
            TestCaseForRemove<K>({1}, 1, {}),
            TestCaseForRemove<K>({1, 1}, 1, {}),
            TestCaseForRemove<K>({1, 1}, 3, {1, 1}),
            TestCaseForRemove<K>({1, 1, 2}, 1, {2}),
            TestCaseForRemove<K>({3, 1, 1}, 1, {3}),
            TestCaseForRemove<K>({4, 1, 4}, 4, {1}),
            TestCaseForRemove<K>({4, 1, 4}, 4, {1}),
            TestCaseForRemove<K>({3, 1, 4}, 4, {3, 1}),
            TestCaseForRemove<K>({3, 1, 4}, 3, {1, 4}),
            TestCaseForRemove<K>({3, 1, 4}, 1, {3, 4}),
            TestCaseForRemove<K>({3, 1, 4}, 5, {3, 1, 4}),
            TestCaseForRemove<K>({3, 8, 4, 9, 4, 8, 4, 4, 1, 2, 4}, 4, {3, 8, 9, 8, 1, 2}),
    };
    run_remove_verify<T, K>(test_cases);
}

template<typename T>
void test_remove_string() {
    std::vector<TestCaseForRemove<std::string>> test_cases = {
            TestCaseForRemove<std::string>({"a"}, "b", {"a"}),
            TestCaseForRemove<std::string>({"a", "b"}, "a", {"b"}),
            TestCaseForRemove<std::string>({"a", "b"}, "b", {"a"}),
            TestCaseForRemove<std::string>({"a", "a"}, "a", {}),
            TestCaseForRemove<std::string>({"abc", "xyz", "def", "p", "xyz", "ac", "xy"},
                                           "xyz",
                                           {"abc", "def", "p", "ac", "xy"}),
    };
    run_remove_verify<T, std::string>(test_cases);
}

template<class T>
class TestCaseForEqual {
public:
    std::vector<T> list1;
    std::vector<T> list2;
    bool expect;

    TestCaseForEqual(const std::vector<T> &list1, const std::vector<T> &list2, bool expect) : list1(list1),
                                                                                              list2(list2),
                                                                                              expect(expect) {}
};

template<typename T, typename K>
void run_equal_verify(std::vector<TestCaseForEqual<K>> test_cases) {
    for (auto test_case: test_cases) {
        T list1(test_case.list1.size());
        fill_list_with_vector(list1, test_case.list1);
        T list2(test_case.list2.size());
        fill_list_with_vector(list2, test_case.list2);

        ASSERT_EQ(test_case.expect, (list1 == list2));
    }
}

template<typename T>
void test_equal_int() {
    std::vector<TestCaseForEqual<int>> test_cases = {
            TestCaseForEqual<int>({}, {}, true),
            TestCaseForEqual<int>({1}, {}, false),
            TestCaseForEqual<int>({}, {2}, false),
            TestCaseForEqual<int>({3}, {3}, true),
            TestCaseForEqual<int>({4, 2}, {3}, false),
            TestCaseForEqual<int>({4, 2}, {4}, false),
            TestCaseForEqual<int>({4, 2}, {2}, false),
            TestCaseForEqual<int>({4, 4}, {4}, false),
            TestCaseForEqual<int>({4, 2}, {4, 2}, true),
            TestCaseForEqual<int>({3}, {5, 3}, false),
            TestCaseForEqual<int>({5}, {5, 3}, false),
            TestCaseForEqual<int>({3}, {3, 3}, false),
            TestCaseForEqual<int>({5, 3}, {5, 3}, true),
            TestCaseForEqual<int>({1, 8, 7, 9}, {1, 8, 7, 9}, true),
    };
    run_equal_verify<T, int>(test_cases);
}

template<typename T>
void test_equal_string() {
    std::vector<TestCaseForEqual<std::string>> test_cases = {
            TestCaseForEqual<std::string>({"a", "uf", "exy"}, {"a", "uf", "exy"}, true),
            TestCaseForEqual<std::string>({"b", "uf", "exy"}, {"a", "uf", "exy"}, false),
            TestCaseForEqual<std::string>({"uf", "exy"}, {"a", "uf", "exy"}, false),
            TestCaseForEqual<std::string>({"aaaa", "bbb"}, {"a", "uf", "exy"}, false),
    };
    run_equal_verify<T, std::string>(test_cases);
}