#include "fibonacci_iterator.h"
#include <gtest/gtest.h>
#include <vector>

namespace fibonacci {

namespace {

TEST(Fibonacci, CustomIterator) {
    std::vector<int> expected{0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89};
    std::vector<int> actual;

    for (auto it = Range().begin(); it != Range().end() && *it <= 89; ++it) {
        actual.push_back(*it);
    }

    EXPECT_EQ(actual, expected);
}

TEST(Fibonacci, BoostIterator) {
    std::vector<int> expected{0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89};
    std::vector<int> actual;

    for (auto it = BoostRange().begin(); it != BoostRange().end() && *it <= 89; ++it) {
        actual.push_back(*it);
    }

    EXPECT_EQ(actual, expected);
}

}  // namespace

}  // namespace fibonacci