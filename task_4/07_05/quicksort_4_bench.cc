#include "quicksort_4.h"
#include <gtest/gtest.h>
#include <benchmark/benchmark.h>

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


static void BM_QuicksortThreshold(benchmark::State& state) {
    const std::size_t threshold = state.range(0);
    std::vector<double> original(10000);
    std::iota(original.rbegin(), original.rend(), 1.0);

    for (auto _ : state) {
        state.PauseTiming();
        std::vector<double> vec = original;
        state.ResumeTiming();

        quicksort::quicksort(vec, threshold);
        benchmark::DoNotOptimize(vec);
    }
}

BENCHMARK(BM_QuicksortThreshold)->Arg(4)->Arg(8)->Arg(16)->Arg(32)->Arg(64);

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::benchmark::Initialize(&argc, argv);
    ::benchmark::RunSpecifiedBenchmarks();
    return RUN_ALL_TESTS();
}