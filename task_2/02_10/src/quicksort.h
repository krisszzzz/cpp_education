#pragma once

#include <cassert>
#include <cstddef>
#include <vector>

namespace quicksort {

void order(std::vector<int>& vector, std::size_t left, std::size_t right);
std::size_t partition(std::vector<int>& vector, std::size_t left, std::size_t right);

void split(std::vector<int>& vector, std::size_t left, std::size_t right);
inline void quicksort(std::vector<int>& vector) { split(vector, 0, std::size(vector)); }

}  // namespace quicksort