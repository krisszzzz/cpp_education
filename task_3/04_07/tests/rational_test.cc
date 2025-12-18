
#include "rational.h"
#include <cstdio>

using namespace rational;

namespace StaticTests {
    static_assert(Ratio<1, 2>::num == 1, "Ratio<1,2>::num should be 1");
    static_assert(Ratio<1, 2>::den == 2, "Ratio<1,2>::den should be 2");

    static_assert(sum<Ratio<1, 2>, Ratio<1, 3>>::num == 5, "1/2 + 1/3 = 5/6");
    static_assert(sum<Ratio<1, 2>, Ratio<1, 3>>::den == 6, "1/2 + 1/3 = 5/6");
    static_assert(sum<Ratio<2, 4>, Ratio<2, 8>>::num == 3, "2/4 + 2/8 = 3/4 (сокращение)");
    static_assert(sum<Ratio<2, 4>, Ratio<2, 8>>::den == 4, "2/4 + 2/8 = 3/4 (сокращение)");

    static_assert(sub<Ratio<1, 2>, Ratio<1, 3>>::num == 1, "1/2 - 1/3 = 1/6");
    static_assert(sub<Ratio<1, 2>, Ratio<1, 3>>::den == 6, "1/2 - 1/3 = 1/6");
    static_assert(sub<Ratio<3, 4>, Ratio<1, 4>>::num == 1, "3/4 - 1/4 = 1/2");
    static_assert(sub<Ratio<3, 4>, Ratio<1, 4>>::den == 2, "3/4 - 1/4 = 1/2");

    static_assert(mul<Ratio<1, 2>, Ratio<2, 3>>::num == 1, "1/2 * 2/3 = 1/3");
    static_assert(mul<Ratio<1, 2>, Ratio<2, 3>>::den == 3, "1/2 * 2/3 = 1/3");
    static_assert(mul<Ratio<2, 4>, Ratio<4, 8>>::num == 1, "2/4 * 4/8 = 1/4");
    static_assert(mul<Ratio<2, 4>, Ratio<4, 8>>::den == 4, "2/4 * 4/8 = 1/4");

    static_assert(div<Ratio<1, 2>, Ratio<1, 3>>::num == 3, "(1/2) / (1/3) = 3/2");
    static_assert(div<Ratio<1, 2>, Ratio<1, 3>>::den == 2, "(1/2) / (1/3) = 3/2");
    static_assert(div<Ratio<2, 3>, Ratio<4, 9>>::num == 3, "(2/3) / (4/9) = 3/2");
    static_assert(div<Ratio<2, 3>, Ratio<4, 9>>::den == 2, "(2/3) / (4/9) = 3/2");

    static_assert(Reduce<Ratio<2, 4>>::type::num == 1, "2/4 = 1/2");
    static_assert(Reduce<Ratio<2, 4>>::type::den == 2, "2/4 = 1/2");
    static_assert(Reduce<Ratio<10, 15>>::type::num == 2, "10/15 сокращается до 2/3");
    static_assert(Reduce<Ratio<10, 15>>::type::den == 3, "10/15 сокращается до 2/3");

    using R1 = Ratio<1, 2>;
    using R2 = Ratio<1, 3>;
    static_assert(std::is_same_v<sum<R1, R2>, Ratio<5, 6>>, "sum alias test");
    static_assert(std::is_same_v<sub<R1, R2>, Ratio<1, 6>>, "sub alias test");
    static_assert(std::is_same_v<mul<R1, R2>, Ratio<1, 6>>, "mul alias test");
    static_assert(std::is_same_v<div<R1, R2>, Ratio<3, 2>>, "div alias test");
}


int main() {
    std::printf("All compile time tests passed\n");
}