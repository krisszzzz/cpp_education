#include "free_list_allocator.h"

Allocator::Allocator(std::size_t size, SearchStrategy strategy)
    : m_size(size), m_strategy(strategy) {
    assert(m_size >= sizeof(Node) + 1);
    
    m_begin = operator new(m_size, std::align_val_t(s_alignment));
    m_head = get_node(m_begin);
    m_head->size = m_size - sizeof(Header);
    m_head->next = nullptr;
}

Allocator::~Allocator() {
    operator delete(m_begin, m_size, std::align_val_t(s_alignment));
}

auto Allocator::allocate(std::size_t size) -> void* {
    void* end = get_byte(m_begin) + sizeof(Header) + size;
    void* next = end;
    auto free = 2 * alignof(Header);

    if (next = std::align(alignof(Header), sizeof(Header), next, free); next) {
        auto padding = get_byte(next) - get_byte(end);
        auto [current, previous] = find(size + padding);

        if (current) {
            if (current->size >= size + padding + sizeof(Node) + 1) {
                auto step = sizeof(Header) + size + padding;
                auto node = get_node(get_byte(current) + step);
                node->size = current->size - step;
                node->next = current->next;
                current->next = node;
            } else {
                padding += current->size - size - padding;
            }

            if (!previous) {
                m_head = current->next;
            } else {
                previous->next = current->next;
            }

            auto header = get_header(current);
            header->size = size + padding;
            return get_byte(current) + sizeof(Header);
        }
    }
    return nullptr;
}

void Allocator::deallocate(void* x) {
    auto node = get_node(get_byte(x) - sizeof(Header));
    Node* previous = nullptr;
    Node* current = m_head;
    
    while (current) {
        if (node < current) {
            node->next = current;
            if (!previous) {
                m_head = node;
            } else {
                previous->next = node;
            }
            break;
        }
        previous = current;
        current  = current->next;
    }
    merge(previous, node);
}

void Allocator::show() const {
    std::print(
        "Chain_Allocator::show : m_size = {} m_begin = {:018} m_head = {:018} ",
        m_size, m_begin, static_cast<void*>(m_head)
    );
    if (m_head->next) {
        std::print("m_head->next = {:018}\n", static_cast<void*>(m_head->next));
    } else {
        std::print("\n");
    }
}

auto Allocator::get_byte(void* x) const -> std::byte* {
    return static_cast<std::byte*>(x);
}

auto Allocator::get_node(void* x) const -> Node* {
    return static_cast<Node*>(x);
}

auto Allocator::get_header(void* x) const -> Header* {
    return static_cast<Header*>(x);
}

auto Allocator::find_first(std::size_t size) const -> std::pair<Node*, Node*> {
    Node* current = m_head;
    Node* previous = nullptr;
    while (current && size > current->size) {
        previous = current;
        current  = current->next;
    }
    return std::make_pair(current, previous);
}

auto Allocator::find_best(std::size_t size) const -> std::pair<Node*, Node*> {
    Node* best = nullptr;
    Node* best_prev = nullptr;
    Node* current = m_head;
    Node* previous = nullptr;
    std::size_t best_size = std::numeric_limits<std::size_t>::max();

    while (current) {
        if (current->size >= size && current->size < best_size) {
            best = current;
            best_prev = previous;
            best_size = current->size;
        }
        previous = current;
        current  = current->next;
    }
    return std::make_pair(best, best_prev);
}

auto Allocator::find(std::size_t size) const -> std::pair<Node*, Node*> {
    if (m_strategy == SearchStrategy::FirstFit) {
        return find_first(size);
    } else {
        return find_best(size);
    }
}

void Allocator::merge(Node* previous, Node* node) const {
    if (node->next && get_byte(node) + sizeof(Header) + node->size == get_byte(node->next)) {
        node->size += sizeof(Header) + node->next->size;
        node->next = node->next->next;
    }
    if (previous && get_byte(previous) + sizeof(Header) + previous->size == get_byte(node)) {
        previous->size += sizeof(Header) + node->size;
        previous->next = node->next;
    }
}

void benchmark_allocator(benchmark::State& state, Allocator::SearchStrategy strategy) {
    auto kb = 1uz << 10;
    auto mb = 1uz << 20;
    auto gb = 1uz << 30;
    std::uniform_int_distribution distribution(1, 16);
    std::default_random_engine engine;
    std::vector<void*> vector(kb, nullptr);

    for (auto element : state) {
        Allocator allocator(16 * gb, strategy);
        for (auto i = 0uz; i < kb; ++i) {
            vector[i] = allocator.allocate(distribution(engine) * mb);
        }
        for (auto i = 0uz; i < kb; i += 32) {
            allocator.deallocate(vector[i]);
        }
        for (auto i = 0uz; i < kb; i += 32) {
            vector[i] = allocator.allocate(distribution(engine) * mb);
        }
        for (auto i = 0uz; i < kb; ++i) {
            allocator.deallocate(vector[i]);
        }
        benchmark::DoNotOptimize(vector);
    }
}

void test_first_fit(benchmark::State& state) {
    benchmark_allocator(state, Allocator::SearchStrategy::FirstFit);
}

void test_best_fit(benchmark::State& state) {
    benchmark_allocator(state, Allocator::SearchStrategy::BestFit);
}

BENCHMARK(test_first_fit)->Name("Allocator_FirstFit");
BENCHMARK(test_best_fit)->Name("Allocator_BestFit");

int main() {
    benchmark::RunSpecifiedBenchmarks();
    return 0;
}