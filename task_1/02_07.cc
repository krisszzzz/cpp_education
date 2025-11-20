#include <iostream>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <vector>

double find_max(const std::vector<double>& vec);
double find_min(const std::vector<double>& vec);
double calculate_mean(const std::vector<double>& vec);
double calculate_std_dev(const std::vector<double>& vec, double mean);

double find_max(const std::vector<double>& vec) {
    auto it = std::max_element(vec.begin(), vec.end());
    return *it;
}

double find_min(const std::vector<double>& vec) {
    auto it = std::min_element(vec.begin(), vec.end());
    return *it;
}

double calculate_mean(const std::vector<double>& vec) {
    double sum = std::accumulate(vec.begin(), vec.end(), 0.0);
    return sum / vec.size();
}

double calculate_std_dev(const std::vector<double>& vec, double mean) {
    double sum_squares = std::accumulate(vec.begin(), vec.end(), 0.0,
        [mean](double acc, double x) {
            double diff = x - mean;
            return acc + diff * diff;
        });
    return std::sqrt(sum_squares / vec.size());
}

int main() {
    std::vector<double> data;
    double value;

    while (std::cin >> value) {
        data.push_back(value);
    }

    if (data.empty()) {
        return 0;
    }

    double max_val = find_max(data);
    double min_val = find_min(data);
    double mean = calculate_mean(data);
    double std_dev = calculate_std_dev(data, mean);

    std::cout << "Max: " << max_val << "\n";
    std::cout << "Min: " << min_val << "\n";
    std::cout << "Mean: " << mean << "\n";
    std::cout << "Standard Deviation: " << std_dev << "\n";

    return 0;
}
