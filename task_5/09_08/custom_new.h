#pragma once

#include <cstddef>
#include <new>
#include <print>

template<typename D>
class Entity {
public:
    static auto operator new(std::size_t size) -> void*;
    static void operator delete(void* x);
    static auto operator new[](std::size_t size) -> void*;
    static void operator delete[](void* x);
    static auto operator new(std::size_t size, const std::nothrow_t& tag) noexcept -> void*;
    static void operator delete(void* x, const std::nothrow_t& tag) noexcept;
    static auto operator new[](std::size_t size, const std::nothrow_t& tag) noexcept -> void*;
    static void operator delete[](void* x, const std::nothrow_t& tag) noexcept;

protected:
    Entity() = default;
};

class Client : private Entity<Client> {
public:
    Client();
    ~Client();

    using Entity<Client>::operator new;
    using Entity<Client>::operator delete;
    using Entity<Client>::operator new[];
    using Entity<Client>::operator delete[];
};