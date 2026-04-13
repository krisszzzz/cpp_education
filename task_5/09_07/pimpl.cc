#include "pimpl.h"

void Entity::Implementation::test() const {
    std::print("Entity::Implementation::test\n");
}

Entity::Entity() {
    static_assert(sizeof(Implementation) <= sizeof(m_storage), "Implementation too large for storage");
    static_assert(alignof(Implementation) <= alignof(std::max_align_t), "Implementation alignment exceeds max_align_t");
    new (m_storage.data()) Implementation();
}

Entity::Entity(Entity&& other) {
    static_assert(sizeof(Implementation) <= sizeof(m_storage), "Implementation too large for storage");
    static_assert(alignof(Implementation) <= alignof(std::max_align_t), "Implementation alignment exceeds max_align_t");
    new (m_storage.data()) Implementation(std::move(*std::launder(std::bit_cast<Implementation*>(other.m_storage.data()))));
    std::destroy_at(std::launder(std::bit_cast<Implementation*>(other.m_storage.data())));
}

Entity::~Entity() {
    std::destroy_at(get());
}

auto& Entity::operator=(Entity&& other) {
    if (this != &other) {
        std::destroy_at(get());
        new (m_storage.data()) Implementation(std::move(*std::launder(std::bit_cast<Implementation*>(other.m_storage.data()))));
        std::destroy_at(std::launder(std::bit_cast<Implementation*>(other.m_storage.data())));
    }
    return *this;
}

void Entity::test() const {
    get()->test();
}

Entity::Implementation* Entity::get() {
    return std::launder(std::bit_cast<Implementation*>(m_storage.data()));
}

const Entity::Implementation* Entity::get() const {
    return std::launder(std::bit_cast<const Implementation*>(m_storage.data()));
}

int main() {
    {
        Entity e1;
        e1.test();
    }

    {
        Entity e2;
        Entity e3(std::move(e2));
        e3.test();
    }

    {
        Entity e4;
        Entity e5;
        e5 = std::move(e4);
        e5.test();
    }

    {
        const Entity e6;
        e6.test();
    }

    return 0;
}