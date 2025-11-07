/*
 * DO NOT MAKE ANY CHANGES
 */

#include "unit_test_map.h"

TEST(problem_1, array_map_init_is_empty) {
    ArrayMap<int, int> hash_map;
    ASSERT_TRUE(hash_map.is_empty());
}

TEST(problem_1, array_map_put_new_key) {
    array_map_put_new_key<int, int>();
    array_map_put_new_key<float, int>();
    array_map_put_new_key<int, float>();
    array_map_put_new_key<float, float>();
}

TEST(problem_1, array_map_remove) {
    array_map_test_remove<int, int>();
    array_map_test_remove<float, int>();
    array_map_test_remove<int, float>();
    array_map_test_remove<float, float>();
}

/*
 * used for problem 2 testing
 */
TEST(problem_1, array_map_list_contructor) {
    ArrayMap<float, float> map = ArrayMap<float, float>(
            {
                    {1, 1.1},
                    {2, 2.2},
            }
    );

    float actual;
    map.get(1, actual);
    ASSERT_FLOAT_EQ(1.1, actual);

    map.get(2, actual);
    ASSERT_FLOAT_EQ(2.2, actual);

    ASSERT_FLOAT_EQ(2, map.size());
}

TEST(problem_1, array_map_list_contructor_2) {
    ArrayMap<float, float> map(
            {
                    {1, 1.3},
                    {2, 2.3},
                    {9, 0.3},
            }
    );

    float actual;
    map.get(1, actual);
    ASSERT_FLOAT_EQ(1.3, actual);

    map.get(2, actual);
    ASSERT_FLOAT_EQ(2.3, actual);

    map.get(9, actual);
    ASSERT_FLOAT_EQ(0.3, actual);

    ASSERT_FLOAT_EQ(3, map.size());
}

TEST(problem_1, array_map_equal) {
    array_map_test_equal<int, int>();
    array_map_test_equal<float, int>();
    array_map_test_equal<int, float>();
    array_map_test_equal<float, float>();
}

TEST(problem_1, array_map_copy_constructor) {
    ArrayMap<float, float> *map_1 = new ArrayMap<float, float>(
            {
                    {2, 2.3},
                    {1, 1.3},
                    {3, 4.4},
            }
    );

    // make a manual copy
    ArrayMap<float, float> map_2(map_1->size());
    map_2.put(1, 1.3);
    map_2.put(3, 4.4);
    map_2.put(2, 2.3);
    ASSERT_TRUE(*map_1 == map_2);

    // call the copy constructor
    ArrayMap<float, float> map_copy(*map_1);

    ASSERT_TRUE(map_copy == *map_1);
    ASSERT_TRUE(map_copy == map_2);

    // verify deep copy
    delete map_1;
    ASSERT_TRUE(map_copy == map_2);
}

TEST(problem_1, array_map_copy_constructor_duplicate_hash_key) {
    const int CAPACITY = 5;
    ArrayMap<float, float> *map_1 = new ArrayMap<float, float>(CAPACITY);
    map_1->put(1, 1.3);
    map_1->put(3, 4.4);
    map_1->put(1 * CAPACITY + 3, 6.9);
    map_1->put(2 * CAPACITY + 3, 12);

    // make a manual copy
    printf("\n");
    ArrayMap<float, float> map_2(CAPACITY);
    map_2.put(2 * CAPACITY + 3, 12);
    map_2.put(1, 1.3);
    map_2.put(1 * CAPACITY + 3, 6.9);
    map_2.put(3, 4.4);
    ASSERT_TRUE(*map_1 == map_2);

    // call the copy constructor
    ArrayMap<float, float> map_copy(*map_1);

    ASSERT_TRUE(map_copy == *map_1);
    ASSERT_TRUE(map_copy == map_2);

    // verify deep copy
    delete map_1;
    ASSERT_TRUE(map_copy == map_2);
}

TEST(problem_1, array_map_keyset) {
    ArrayMap<int, float> map(3);
    map.put(1, 1.1);
    map.put(3, 3.3);
    map.put(4, 4.4);
    std::set<int> expect = {1, 3, 4};
    ArrayList<int> keys(100);
    map.key_set(keys);

    ASSERT_EQ(expect.size(), keys.size());
    for (int i = 0; i < keys.size(); i++) {
        ASSERT_TRUE(expect.find(keys[i]) != expect.end());
    }
}
