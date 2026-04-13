#include "quicksort.h"
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

namespace quicksort {

template<typename RandIt>
void order(RandIt first, RandIt last) {
    if (first == last) return;
    for (auto i = std::next(first); i != last; ++i) {
        for (auto j = i; j != first; --j) {
            auto prev_j = std::prev(j);
            if (*prev_j > *j) {
                std::iter_swap(j, prev_j);
            }
        }
    }
}

template<typename RandIt>
RandIt partition(RandIt first, RandIt last) {
    auto dist = std::distance(first, last);
    auto mid = std::next(first, dist / 2);
    auto middle_val = *mid;

    auto i = first;
    auto j = std::prev(last);

    while (true) {
        while (*i < middle_val) {
            ++i;
        }
        while (*j > middle_val) {
            --j;
        }
        if (i >= j) {
            return j;
        }
        std::iter_swap(i, j);
        ++i;
        --j;
    }
}

template<typename RandIt>
void split(RandIt first, RandIt last) {
    auto dist = std::distance(first, last);
    if (dist > 16) {
        auto mid = std::next(first, dist / 2);
        auto prev_last = std::prev(last);

        if (*mid < *first) {
            std::iter_swap(mid, first);
        }
        if (*prev_last < *first) {
            std::iter_swap(prev_last, first);
        }
        if (*prev_last < *mid) {
            std::iter_swap(prev_last, mid);
        }

        auto p = partition(first, last);
        split(first, std::next(p));
        split(std::next(p), last);

    } else {
        order(first, last);
    }
}

template<typename RandIt>
void quicksort(RandIt first, RandIt last) {
    if (first != last) {
        split(first, last);
    }
}

template<typename Container>
void quicksort(Container& container) {
    quicksort(std::begin(container), std::end(container));
}

template void order(std::vector<double>::iterator, std::vector<double>::iterator);
template void order(std::vector<std::string>::iterator, std::vector<std::string>::iterator);
template void order(std::vector<char>::iterator, std::vector<char>::iterator);

template void split(std::vector<double>::iterator, std::vector<double>::iterator);
template void split(std::vector<std::string>::iterator, std::vector<std::string>::iterator);
template void split(std::vector<char>::iterator, std::vector<char>::iterator);

template void quicksort(std::vector<double>::iterator, std::vector<double>::iterator);
template void quicksort(std::vector<std::string>::iterator, std::vector<std::string>::iterator);
template void quicksort(std::vector<char>::iterator, std::vector<char>::iterator);

template void quicksort(std::vector<double>&);
template void quicksort(std::vector<std::string>&);
template void quicksort(std::vector<char>&);

}  // namespace quicksort