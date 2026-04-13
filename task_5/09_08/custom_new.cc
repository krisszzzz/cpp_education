#include "custom_new.h"

template<typename D>
auto Entity<D>::operator new(std::size_t size) -> void* {
    std::print("Entity::operator new\n");
    return ::operator new(size);
}

template<typename D>
void Entity<D>::operator delete(void* x) {
    std::print("Entity::operator delete\n");
    ::operator delete(x);
}

template<typename D>
auto Entity<D>::operator new[](std::size_t size) -> void* {
    std::print("Entity::operator new[]\n");
    return ::operator new[](size);
}

template<typename D>
void Entity<D>::operator delete[](void* x) {
    std::print("Entity::operator delete[]\n");
    ::operator delete[](x);
}

template<typename D>
auto Entity<D>::operator new(std::size_t size, const std::nothrow_t& tag) noexcept -> void* {
    std::print("Entity::operator new(nothrow)\n");
    return ::operator new(size, tag);
}

template<typename D>
void Entity<D>::operator delete(void* x, const std::nothrow_t& tag) noexcept {
    std::print("Entity::operator delete(nothrow)\n");
    ::operator delete(x);
}

template<typename D>
auto Entity<D>::operator new[](std::size_t size, const std::nothrow_t& tag) noexcept -> void* {
    std::print("Entity::operator new[](nothrow)\n");
    return ::operator new[](size, tag);
}

template<typename D>
void Entity<D>::operator delete[](void* x, const std::nothrow_t& tag) noexcept {
    std::print("Entity::operator delete[](nothrow)\n");
    ::operator delete[](x);
}

template class Entity<Client>;

Client::Client() {
    std::print("Client::Client\n");
}

Client::~Client() {
    std::print("Client::~Client\n");
}

int main() {
    std::print("new/delete\n");
    delete new Client;

    std::print("\nnew[]/delete[]\n");
    delete[] new Client[3];

    std::print("\nnew(nothrow)/delete\n");
    delete new(std::nothrow) Client;

    std::print("\nnew[](nothrow)/delete[]\n");
    delete[] new(std::nothrow) Client[2];

    return 0;
}