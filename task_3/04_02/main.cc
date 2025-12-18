#include <iostream>
#include <type_traits>
#include <limits>

template<typename T>
T max_value(T value) {
    return value;
}

template<typename T, typename... Args>
T max_value(T first, Args... args) {
    T max_rest = max_value(args...);
    return first > max_rest ? first : max_rest;
}

template<typename T>
T min_value(T value) {
    return value;
}

template<typename T, typename... Args>
T min_value(T first, Args... args) {
    T min_rest = min_value(args...);
    return first < min_rest ? first : min_rest;
}

template<typename... Args>
auto sum(Args... args) {
    static_assert((std::is_same<Args, double>::value && ...), "All arguments must be double");
    return (args + ...);
}

template<typename... Args>
double average(Args... args) {
    static_assert((std::is_same<Args, double>::value && ...), "All arguments must be double");
    static_assert(sizeof...(args) > 0, "At least one argument required");
    return (args + ...) / static_cast<double>(sizeof...(args));
}

int main() {
    std::cout.precision(6);
    std::cout << std::fixed;

    std::cout << "  Max: " << max_value(1.5, 2.5, 3.5, 4.5, 5.5) << "\n";
    std::cout << "  Min: " << min_value(1.5, 2.5, 3.5, 4.5, 5.5) << "\n";
    std::cout << "  Sum: " << sum(1.5, 2.5, 3.5, 4.5, 5.5) << "\n";
    std::cout << "  Avg: " << average(1.5, 2.5, 3.5, 4.5, 5.5) << "\n";

    return 0;
}