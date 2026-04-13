#pragma once

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <numeric>
#include <utility>
#include <vector>

namespace quicksort {

template<typename RandIt>
void order(RandIt first, RandIt last);

template<typename RandIt>
RandIt partition(RandIt first, RandIt last);

template<typename RandIt>
void split(RandIt first, RandIt last);

template<typename RandIt>
void quicksort(RandIt first, RandIt last);

template<typename Container>
void quicksort(Container& container);

}  // namespace quicksort