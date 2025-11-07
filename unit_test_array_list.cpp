/*
 * DO NOT MAKE ANY CHANGES
 */

#include "gtest/gtest.h"
#include "problem_1/array_list.h"
#include "unit_test_array_list.hpp"

TEST(problem_1, new_array_list_with_capacity) {
    test_new_array_list_size_capacity<ArrayList<int>>();
}

TEST(problem_1, copy_constructor) {
    test_copy_constructor<ArrayList<int>>();
}

TEST(problem_1, push_back) {
    test_push_back<ArrayList<int>>();
}

TEST(problem_1, push_front) {
    test_push_front<ArrayList<int>>();
}

TEST(problem_1, pop_back) {
    test_pop_back<ArrayList<int>>();
}

TEST(problem_1, pop_front) {
    test_pop_front<ArrayList<int>>();
}

TEST(problem_1, merge) {
    test_merge_int<ArrayList<int>>();
    test_merge_string<ArrayList<std::string>>();
    test_merge_float<ArrayList<float>>();
}

TEST(problem_1, remove) {
    test_remove_primitive_number<ArrayList<int>, int>();
    test_remove_primitive_number<ArrayList<float>, float>();
    test_remove_string<ArrayList<std::string>>();
}

TEST(problem_1, equal) {
    test_equal_int<ArrayList<int>>();
    test_equal_string<ArrayList<std::string>>();
}