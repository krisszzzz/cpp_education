
#include "quicksort_4.h"


TEST(QuickSort, DoubleType) {
    std::vector<double> vector{3.14, 2.71, 1.41, 1.73, 0.0, -1.0, 2.5};

    quicksort::quicksort(vector);
    EXPECT_TRUE(std::ranges::is_sorted(vector));
}

TEST(QuickSort, StringType) {
    std::vector<std::string> vector{"banana", "apple", "cherry", "date", "fig"};

    quicksort::quicksort(vector);
    EXPECT_TRUE(std::ranges::is_sorted(vector));
}

TEST(QuickSort, CharType) {
    std::vector<char> vector{'z', 'a', 'm', 'b', 'k', 'c'};

    quicksort::quicksort(vector);
    EXPECT_TRUE(std::ranges::is_sorted(vector));
}



TEST(QuickSort, CustomType) {
    std::vector<Person> vector{
        {"Alice", 25},
        {"Bob", 30},
        {"Charlie", 20},
        {"David", 35}
    };

    quicksort::quicksort(vector);
    EXPECT_TRUE(std::ranges::is_sorted(vector, [](const Person& a, const Person& b) {
        return a.age < b.age;
    }));
}
