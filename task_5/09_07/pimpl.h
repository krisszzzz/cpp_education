#pragma once

#include <array>
#include <cstddef>
#include <new>
#include <memory>
#include <bit>
#include <print>
#include <utility>

class Entity {
private:
    class Implementation {
    public:
        Implementation() = default;
        Implementation(const Implementation&) = delete;
        Implementation& operator=(const Implementation&) = delete;
        Implementation(Implementation&&) = default;
        Implementation& operator=(Implementation&&) = default;
        ~Implementation() = default;

        void test() const;
    };

    alignas(std::max_align_t) std::array<std::byte, 16> m_storage;

public:
    Entity();
    Entity(Entity&& other);
    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;
    ~Entity();

    auto& operator=(Entity&& other);

    void test() const;

    Implementation* get();
    const Implementation* get() const;
};