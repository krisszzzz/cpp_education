#pragma once

#include <cassert>
#include <cstddef>
#include <memory>
#include <new>
#include <print>
#include <random>
#include <utility>
#include <vector>
#include <limits>

#include <benchmark/benchmark.h>

class Allocator {
public:
    enum class SearchStrategy { FirstFit, BestFit };

    explicit Allocator(std::size_t size, SearchStrategy strategy = SearchStrategy::FirstFit);
    Allocator(const Allocator&) = delete;
    Allocator& operator=(const Allocator&) = delete;
    Allocator(Allocator&&) = delete;
    Allocator& operator=(Allocator&&) = delete;

    ~Allocator();

    auto allocate(std::size_t size) -> void*;
    void deallocate(void* x);
    void show() const;

private:
    struct Node { 
        std::size_t size = 0;
        Node* next = nullptr;
    };

    struct alignas(std::max_align_t) Header { 
        std::size_t size = 0;
    };

    auto get_byte(void* x) const -> std::byte*;
    auto get_node(void* x) const -> Node*;
    auto get_header(void* x) const -> Header*;
    auto find_first(std::size_t size) const -> std::pair<Node*, Node*>;
    auto find_best(std::size_t size) const -> std::pair<Node*, Node*>;
    auto find(std::size_t size) const -> std::pair<Node*, Node*>;
    void merge(Node* previous, Node* node) const;

    std::size_t m_size = 0;
    void* m_begin = nullptr;
    Node* m_head  = nullptr;
    SearchStrategy m_strategy = SearchStrategy::FirstFit;

    static inline auto s_alignment = alignof(std::max_align_t);
};

void benchmark_allocator(benchmark::State& state, Allocator::SearchStrategy strategy);
void test_first_fit(benchmark::State& state);
void test_best_fit(benchmark::State& state);

BENCHMARK(test_first_fit)->Name("Allocator_FirstFit");
BENCHMARK(test_best_fit)->Name("Allocator_BestFit");