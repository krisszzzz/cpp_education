#pragma once

#include <limits>

template<int N>
struct Fibonacci {
    static_assert(N >= 0, "Fibonacci index must be non-negative");

    static constexpr int value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;

    static_assert(
        Fibonacci<N - 1>::value <= std::numeric_limits<int>::max() - Fibonacci<N - 2>::value,
        "Integer overflow in Fibonacci computation"
    );
};

template<>
struct Fibonacci<0> {
    static constexpr int value = 0;
};

template<>
struct Fibonacci<1> {
    static constexpr int value = 1;
};

template<int N>
inline constexpr int fibonacci_v = Fibonacci<N>::value;