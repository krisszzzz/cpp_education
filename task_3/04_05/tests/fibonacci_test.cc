
#include "fibonacci.h"
#include <cstdio>

namespace StaticTests {
    static_assert(Fibonacci<0>::value == 0, "F(0) should be 0");
    static_assert(Fibonacci<1>::value == 1, "F(1) should be 1");
    static_assert(Fibonacci<2>::value == 1, "F(2) should be 1");
    static_assert(Fibonacci<3>::value == 2, "F(3) should be 2");
    static_assert(Fibonacci<4>::value == 3, "F(4) should be 3");
    static_assert(Fibonacci<5>::value == 5, "F(5) should be 5");

    static_assert(Fibonacci<6>::value == 8, "F(6) should be 8");
    static_assert(Fibonacci<7>::value == 13, "F(7) should be 13");
    static_assert(Fibonacci<8>::value == 21, "F(8) should be 21");
    static_assert(Fibonacci<9>::value == 34, "F(9) should be 34");
    static_assert(Fibonacci<10>::value == 55, "F(10) should be 55");

    static_assert(fibonacci_v<0> == 0, "fibonacci_v<0> should be 0");
    static_assert(fibonacci_v<1> == 1, "fibonacci_v<1> should be 1");
    static_assert(fibonacci_v<5> == 5, "fibonacci_v<5> should be 5");
    static_assert(fibonacci_v<10> == 55, "fibonacci_v<10> should be 55");
}


int main() {
    std::printf("All compile time tests passed\n");
}
