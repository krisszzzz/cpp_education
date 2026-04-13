#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <chrono>
#include <cstdint>
#include <iomanip>
#include <iostream>

namespace fibonacci {

namespace ublas = boost::numeric::ublas;

using Matrix = ublas::matrix<unsigned long long int>;
using Value = unsigned long long int;

auto matrix_multiply(const Matrix& a, const Matrix& b) -> Matrix {
    Matrix result(2, 2);
    for (std::size_t i = 0; i < 2; ++i) {
        for (std::size_t j = 0; j < 2; ++j) {
            result(i, j) = 0;
            for (std::size_t k = 0; k < 2; ++k) {
                result(i, j) += a(i, k) * b(k, j);
            }
        }
    }
    return result;
}

auto matrix_power(Matrix base, unsigned long long int exp) -> Matrix {
    Matrix result(2, 2);
    result(0, 0) = 1;
    result(0, 1) = 0;
    result(1, 0) = 0;
    result(1, 1) = 1;

    while (exp > 0) {
        if (exp & 1) {
            result = matrix_multiply(result, base);
        }
        base = matrix_multiply(base, base);
        exp >>= 1;
    }
    return result;
}

auto fibonacci(unsigned long long int n) -> Value {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }

    Matrix base(2, 2);
    base(0, 0) = 1;
    base(0, 1) = 1;
    base(1, 0) = 1;
    base(1, 1) = 0;

    Matrix result = matrix_power(base, n - 1);
    return result(0, 0);
}

auto fibonacci_iterative(unsigned long long int n) -> Value {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    
    Value prev = 0;
    Value curr = 1;
    for (unsigned long long int i = 2; i <= n; ++i) {
        Value next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}

void benchmark_fibonacci() {
    std::cout << "\n=== Performance Comparison ===\n";
    std::cout << std::left << std::setw(10) << "N" 
              << std::setw(20) << "Matrix (log n)" 
              << std::setw(20) << "Iterative (n)" << '\n';
    std::cout << std::string(50, '-') << '\n';

    for (unsigned long long int n : {10, 100, 1000, 10000, 100000, 1000000}) {
        auto start = std::chrono::high_resolution_clock::now();
        [[maybe_unused]] volatile Value r1 = fibonacci(n);
        auto end = std::chrono::high_resolution_clock::now();
        auto t1 = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        start = std::chrono::high_resolution_clock::now();
        [[maybe_unused]] volatile Value r2 = fibonacci_iterative(n);
        end = std::chrono::high_resolution_clock::now();
        auto t2 = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        std::cout << std::left << std::setw(10) << n 
                  << std::setw(20) << t1 
                  << std::setw(20) << t2 << '\n';
    }
}

}  // namespace fibonacci

int main() {
    fibonacci::benchmark_fibonacci();
    return 0;
}
