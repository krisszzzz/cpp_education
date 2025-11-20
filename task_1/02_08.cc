#include <iostream>
#include <vector>

const size_t kCacheSize = 1000;

std::size_t collatz_length(unsigned long long int n, std::vector<size_t>& cache) {
    if (n == 1) return 1;
    if (n < cache.size() && cache[n] != 0) return cache[n];

    unsigned long long int next = (n % 2 == 0) ? n / 2 : 3 * n + 1;
    size_t len = 1 + collatz_length(next, cache);

    if (n < cache.size()) cache[n] = len;
    return len;
}

int main() {
    std::vector<size_t> cache(kCacheSize, 0);
    cache[1] = 1;

    const unsigned long long int kMaxStart = 100;
    size_t max_length = 0;
    unsigned long long int starting_value = 1;

    for (unsigned long long int i = 1; i <= kMaxStart; ++i) {
        size_t len = collatz_length(i, cache);
        if (len > max_length) {
            max_length = len;
            starting_value = i;
        }
    }

    std::cout << "Max length: " << max_length << "\n";
    std::cout << "Starting value: " << starting_value << "\n";

    return 0;
}
