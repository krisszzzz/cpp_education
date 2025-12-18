#include "variadic_insert.h"
#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <deque>

TEST(VariadicInsertTest, InsertOnlyInts) {
    std::vector<int> vec;
    insert_pack(vec, 1, 2, 3, 4, 5);

    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
    EXPECT_EQ(vec[3], 4);
    EXPECT_EQ(vec[4], 5);
}

TEST(VariadicInsertTest, InsertMixedTypes) {
    std::vector<int> vec;
    insert_pack(vec, 10, 3.14, 'a', 20, "string", 30, 40.0, 40);

    EXPECT_EQ(vec.size(), 4);
    EXPECT_EQ(vec[0], 10);
    EXPECT_EQ(vec[1], 20);
    EXPECT_EQ(vec[2], 30);
    EXPECT_EQ(vec[3], 40);
}

TEST(VariadicInsertTest, InsertNoInts) {
    std::vector<int> vec;
    insert_pack(vec, 3.14, 'b', "test", 2.71, true);

    EXPECT_EQ(vec.size(), 0);
    EXPECT_TRUE(vec.empty());
}

TEST(VariadicInsertTest, InsertEmptyPack) {
    std::vector<int> vec;
    insert_pack(vec);

    EXPECT_EQ(vec.size(), 0);
    EXPECT_TRUE(vec.empty());
}

TEST(VariadicInsertTest, InsertToList) {
    std::list<int> lst;
    insert_pack(lst, 1, 2.5, 3, 'c', 4);

    EXPECT_EQ(lst.size(), 3);

    auto it = lst.begin();
    EXPECT_EQ(*it++, 1);
    EXPECT_EQ(*it++, 3);
    EXPECT_EQ(*it++, 4);
}

TEST(VariadicInsertTest, InsertToDeque) {
    std::deque<int> deq;
    insert_pack(deq, 100, 200.5, 300, "skip", 400);

    EXPECT_EQ(deq.size(), 3);
    EXPECT_EQ(deq[0], 100);
    EXPECT_EQ(deq[1], 300);
    EXPECT_EQ(deq[2], 400);
}

TEST(VariadicInsertTest, InsertLargePack) {
    std::vector<int> vec;
    insert_pack(vec,
                1, 2.0, 3, 'a', 4, "test", 5.5, 6,
                7, 8.8, 9, nullptr, 10, true, 11);

    EXPECT_EQ(vec.size(), 8);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 3);
    EXPECT_EQ(vec[2], 4);
    EXPECT_EQ(vec[3], 6);
    EXPECT_EQ(vec[4], 7);
    EXPECT_EQ(vec[5], 9);
    EXPECT_EQ(vec[6], 10);
    EXPECT_EQ(vec[7], 11);
}

TEST(VariadicInsertTest, InsertNegativeNumbers) {
    std::vector<int> vec;
    insert_pack(vec, -1, -2.5, -3, 'x', -4);

    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], -1);
    EXPECT_EQ(vec[1], -3);
    EXPECT_EQ(vec[2], -4);
}
