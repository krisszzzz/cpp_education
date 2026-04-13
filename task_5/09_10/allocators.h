#pragma once

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <memory>
#include <new>
#include <utility>
#include <vector>

#include <benchmark/benchmark.h>

class Allocator {
public:
    virtual ~Allocator() = default;
    
    virtual auto allocate(std::size_t size = 1, std::size_t alignment = alignof(std::max_align_t)) -> void* = 0;
    virtual void deallocate(void* x) = 0;
    virtual void show() const = 0;
    
protected:
    template<typename T>
    auto get_byte(T* x) const -> std::byte* {
        return static_cast<std::byte*>(static_cast<void*>(x));
    }
    
    static constexpr auto s_alignment = alignof(std::max_align_t);
};

class LinearAllocator : public Allocator {
public:
    explicit LinearAllocator(std::size_t size);
    ~LinearAllocator() override;
    
    auto allocate(std::size_t size, std::size_t alignment = s_alignment) -> void* override;
    void deallocate(void*) override;
    void show() const override;
    
private:
    std::size_t m_size = 0;
    std::size_t m_offset = 0;
    void* m_begin = nullptr;
};

class StackAllocator : public Allocator {
public:
    explicit StackAllocator(std::size_t size);
    ~StackAllocator() override;
    
    auto allocate(std::size_t size, std::size_t alignment = s_alignment) -> void* override;
    void deallocate(void* x) override;
    void show() const override;
    
private:
    using header_t = std::uint8_t;
    
    auto get_header(std::byte* x) const -> header_t*;
    
    std::size_t m_size = 0;
    std::size_t m_offset = 0;
    void* m_begin = nullptr;
};

class ListAllocator : public Allocator {
public:
    explicit ListAllocator(std::size_t size, std::size_t step);
    ~ListAllocator() override;
    
    auto allocate(std::size_t = 1, std::size_t = s_alignment) -> void* override;
    void deallocate(void* x) override;
    void show() const override;
    
private:
    struct Node {
        Node* next = nullptr;
    };
    
    auto get_node(void* x) const -> Node*;
    void make_list();
    
    std::size_t m_size = 0;
    std::size_t m_step = 0;
    std::size_t m_offset = 0;
    void* m_begin = nullptr;
    Node* m_head = nullptr;
    std::vector<void*> m_lists;
};

class FreeListAllocator : public Allocator {
public:
    explicit FreeListAllocator(std::size_t size);
    ~FreeListAllocator() override;
    
    auto allocate(std::size_t size, std::size_t alignment = s_alignment) -> void* override;
    void deallocate(void* x) override;
    void show() const override;
    
private:
    struct Node {
        std::size_t size = 0;
        Node* next = nullptr;
    };
    
    struct alignas(std::max_align_t) Header {
        std::size_t size = 0;
    };
    
    auto get_node(void* x) const -> Node*;
    void merge(Node* previous, Node* node) const;
    
    std::size_t m_size = 0;
    void* m_begin = nullptr;
    Node* m_head = nullptr;
};

void test_allocator(Allocator& allocator, const char* name);

static void benchmark_allocator(benchmark::State& state, std::unique_ptr<Allocator> allocator);
static void benchmark_linear(benchmark::State& state);
static void benchmark_stack(benchmark::State& state);
static void benchmark_list(benchmark::State& state);
static void benchmark_freelist(benchmark::State& state);

BENCHMARK(benchmark_linear)->Name("LinearAllocator");
BENCHMARK(benchmark_stack)->Name("StackAllocator");
BENCHMARK(benchmark_list)->Name("ListAllocator");
BENCHMARK(benchmark_freelist)->Name("FreeListAllocator");