#include "quicksort.h"
#include <gtest/gtest.h>
#include <string>
#include <vector>

namespace quicksort {

TEST(QuickSort, DoubleType) {
    std::vector<double> vec{3.14, 2.71, 1.41, 1.73, 0.0, -1.0, 2.5};

    quicksort(vec);
    EXPECT_TRUE(std::ranges::is_sorted(vec));
}

TEST(QuickSort, StringType) {
    std::vector<std::string> vec{"banana", "apple", "cherry", "date", "fig"};

    quicksort(vec);
    EXPECT_TRUE(std::ranges::is_sorted(vec));
}

TEST(QuickSort, CharType) {
    std::vector<char> vec{'z', 'a', 'm', 'b', 'k', 'c'};

    quicksort(vec);
    EXPECT_TRUE(std::ranges::is_sorted(vec));
}

struct Person {
    std::string name;
    int age;

    bool operator>(const Person& other) const {
        return age > other.age;
    }

    bool operator<(const Person& other) const {
        return age < other.age;
    }

    bool operator==(const Person& other) const {
        return age == other.age && name == other.name;
    }
};

TEST(QuickSort, CustomType) {
    std::vector<Person> vec{
        {"Alice", 25},
        {"Bob", 30},
        {"Charlie", 20},
        {"David", 35}
    };

    quicksort(vec);
    EXPECT_TRUE(std::ranges::is_sorted(vec, [](const Person& a, const Person& b) {
        return a.age < b.age;
    }));
}

}  // namespace quicksort