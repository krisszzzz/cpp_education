#include "tuple.h"
#include <cstdio>

namespace StaticTests {

static_assert([]() {
    constexpr Tuple<int, double, char> tuple(42, 3.14, 'A');
    return tuple.get<0>() == 42 &&
           tuple.get<1>() == 3.14 &&
           tuple.get<2>() == 'A';
}(), "Tuple construction and element access");

static_assert([]() {
    constexpr Tuple<int> single_tuple(1);
    constexpr Tuple<int, double> double_tuple(1, 2.0);
    constexpr Tuple<int, double, char> triple_tuple(1, 2.0, 'a');

    return single_tuple.size() == 1 &&
           double_tuple.size() == 2 &&
           triple_tuple.size() == 3;
}(), "Tuple size method");

static_assert([]() {
    constexpr Tuple<int, int> tuple(10, 20);
    constexpr auto sum = tuple.template get<0>() + tuple.get<1>();
    return sum == 30;
}(), "Constexpr computations with tuple");

static_assert([]() {
    constexpr Tuple<int, double, bool, char> tuple(100, 2.718, true, 'Z');

    return tuple.get<0>() == 100 &&
           tuple.get<1>() == 2.718 &&
           tuple.get<2>() == true &&
           tuple.get<3>() == 'Z' &&
           tuple.size() == 4;
}(), "Tuple with multiple different types");

static_assert([]() {
    constexpr Tuple<int, Tuple<double, char>> nested_tuple(42, Tuple<double, char>(3.14, 'X'));

    return nested_tuple.get<0>() == 42 &&
           nested_tuple.get<1>().get<0>() == 3.14 &&
           nested_tuple.get<1>().get<1>() == 'X' &&
           nested_tuple.size() == 2 &&
           nested_tuple.get<1>().size() == 2;
}(), "Nested tuples");

static_assert([]() {
    constexpr auto tuple1 = make_tuple(1, 2.0, 'a');
    constexpr auto tuple2 = make_tuple(10, 20, 30);

    return tuple1.get<0>() == 1 &&
           tuple1.get<1>() == 2.0 &&
           tuple1.get<2>() == 'a' &&
           tuple2.get<0>() == 10 &&
           tuple2.get<1>() == 20 &&
           tuple2.get<2>() == 30 &&
           tuple1.size() == 3 &&
           tuple2.size() == 3;
}(), "make_tuple helper function");

static_assert([]() {
    static constexpr int x = 100;
    static constexpr double y = 3.14159;
    static constexpr char z = 'C';

    constexpr Tuple<const int&, const double&, const char&> ref_tuple(x, y, z);

    return ref_tuple.get<0>() == 100 &&
           ref_tuple.get<1>() == 3.14159 &&
           ref_tuple.get<2>() == 'C' &&
           ref_tuple.size() == 3;
}(), "Tuple with references and constants");

static_assert([]() {
    constexpr Tuple<int> single_tuple(42);
    return single_tuple.get<0>() == 42 &&
           single_tuple.size() == 1;
}(), "Single element tuple");

static_assert([]() {
    constexpr Tuple<int, int, int> tuple1(1, 2, 3);
    constexpr Tuple<int, int, int> tuple2(4, 5, 6);

    constexpr auto sum1 = tuple1.get<0>() + tuple1.get<1>() + tuple1.get<2>();
    constexpr auto sum2 = tuple2.get<0>() + tuple2.get<1>() + tuple2.get<2>();

    return sum1 == 6 &&
           sum2 == 15 &&
           tuple1.size() == 3 &&
           tuple2.size() == 3;
}(), "Value comparisons");

static_assert([]() {
    constexpr Tuple<int, double> tuple(10, 2.5);

    constexpr auto product = tuple.get<0>() * tuple.get<1>();
    constexpr auto quotient = tuple.get<0>() / tuple.get<1>();
    constexpr auto sum = tuple.get<0>() + tuple.get<1>();
    constexpr auto difference = tuple.get<0>() - tuple.get<1>();

    return product == 25.0 &&
           quotient == 4 &&
           sum == 12.5 &&
           difference == 7.5 &&
           tuple.size() == 2;
}(), "Tuple with arithmetic operations");

static_assert([]() {
    constexpr Tuple<int, Tuple<double, Tuple<char, bool>>> complex_tuple(
        1,
        Tuple<double, Tuple<char, bool>>(
            2.0,
            Tuple<char, bool>('a', true)
        )
    );

    return complex_tuple.get<0>() == 1 &&
           complex_tuple.get<1>().get<0>() == 2.0 &&
           complex_tuple.get<1>().get<1>().get<0>() == 'a' &&
           complex_tuple.get<1>().get<1>().get<1>() == true &&
           complex_tuple.size() == 2 &&
           complex_tuple.get<1>().size() == 2 &&
           complex_tuple.get<1>().get<1>().size() == 2;
}(), "Multi-level tuple access");

static_assert([]() {
    constexpr Tuple<int> t1(1);
    constexpr Tuple<int, int> t2(1, 2);
    constexpr Tuple<int, int, int> t3(1, 2, 3);
    constexpr Tuple<int, int, int, int> t4(1, 2, 3, 4);
    constexpr Tuple<int, int, int, int, int> t5(1, 2, 3, 4, 5);

    return t1.size() == 1 &&
           t2.size() == 2 &&
           t3.size() == 3 &&
           t4.size() == 4 &&
           t5.size() == 5;
}(), "sizeof... in size() method");

static_assert([]() {
    constexpr Tuple<int, double, char, bool> tuple(1, 2.0, 'a', false);

    return tuple.get<0>() == 1 &&
           tuple.get<1>() == 2.0 &&
           tuple.get<2>() == 'a' &&
           tuple.get<3>() == false &&
           tuple.size() == 4;
}(), "Element order preservation");

} // namespace StaticTests

int main() {
    std::printf("All compile time tests passed\n");
}