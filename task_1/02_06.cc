#include <iostream>
#include <algorithm>
#include <numeric>
#include <cmath>

constexpr size_t kMaxArraySize = 1000;

double find_max(const double* arr, size_t n) {
    auto it = std::max_element(arr, arr + n);
    return *it;
}

double find_min(const double* arr, size_t n) {
    auto it = std::min_element(arr, arr + n);
    return *it;
}

double calculate_mean(const double* arr, size_t n) {
    double sum = std::accumulate(arr, arr + n, 0.0);
    return sum / n;
}

double calculate_std_dev(const double* arr, size_t n, double mean) {
    double sum_squares = std::accumulate(arr, arr + n, 0.0,
        [mean](double acc, double x) {
            double diff = x - mean;
            return acc + diff * diff;
        });
    return std::sqrt(sum_squares / n);
}

int main() {
    double data[kMaxArraySize];
    size_t count = 0;

    while (std::cin >> data[count] && count < kMaxArraySize) {
        ++count;
    }

    if (count == 0) {
        return 0;
    }

    double max_val = find_max(data, count);
    double min_val = find_min(data, count);
    double mean = calculate_mean(data, count);
    double std_dev = calculate_std_dev(data, count, mean);

    std::cout << "Max: " << max_val << "\n";
    std::cout << "Min: " << min_val << "\n";
    std::cout << "Mean: " << mean << "\n";
    std::cout << "Standard Deviation: " << std_dev << "\n";

    return 0;
}
