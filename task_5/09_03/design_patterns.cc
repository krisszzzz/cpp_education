#include "design_patterns.h"
#include <cassert>
#include <iostream>

namespace design_patterns {

std::unique_ptr<Entity> Builder::make_entity() {
    m_entity = std::make_unique<Entity>();
    set_x();
    set_y();
    return std::move(m_entity);
}

void BuilderClient::set_x() const {
    m_entity->x = 1;
}

void BuilderClient::set_y() const {
    m_entity->y = 1;
}

void BuilderServer::set_x() const {
    m_entity->x = 2;
}

void BuilderServer::set_y() const {
    m_entity->y = 2;
}

int ClientEntity::get_id() const {
    return 1;
}

int ServerEntity::get_id() const {
    return 2;
}

std::unique_ptr<EntityBase> FactoryClient::make_entity() const {
    return std::make_unique<ClientEntity>();
}

std::unique_ptr<EntityBase> FactoryServer::make_entity() const {
    return std::make_unique<ServerEntity>();
}

std::unique_ptr<IPrototype> ClientPrototype::copy() const {
    return std::make_unique<ClientPrototype>(*this);
}

int ClientPrototype::get_id() const {
    return 1;
}

std::unique_ptr<IPrototype> ServerPrototype::copy() const {
    return std::make_unique<ServerPrototype>(*this);
}

int ServerPrototype::get_id() const {
    return 2;
}

Prototype::Prototype() {
    m_entities.push_back(std::make_unique<ClientPrototype>());
    m_entities.push_back(std::make_unique<ServerPrototype>());
}

std::unique_ptr<IPrototype> Prototype::make_client() {
    return m_entities.at(0)->copy();
}

std::unique_ptr<IPrototype> Prototype::make_server() {
    return m_entities.at(1)->copy();
}

int ClientComponent::test() const {
    return 1;
}

int ServerComponent::test() const {
    return 2;
}

void Composite::add(std::unique_ptr<Component> component) {
    m_components.push_back(std::move(component));
}

int Composite::test() const {
    int x = 0;
    for (const auto& component : m_components) {
        if (component) {
            x += component->test();
        }
    }
    return x;
}

void Subject::add(std::shared_ptr<IObserver> observer) {
    m_observers.push_back(observer);
}

void Subject::set(int x) {
    m_x = x;
    notify_all();
}

void Subject::notify_all() const {
    for (const auto& observer : m_observers) {
        if (observer) {
            observer->test(m_x);
        }
    }
}

void ClientObserver::test(int x) const {
    std::cout << "Client::test : x = " << x << '\n';
}

void ServerObserver::test(int x) const {
    std::cout << "Server::test : x = " << x << '\n';
}

void test_builder_pattern() {
    std::cout << "Builder Pattern" << '\n';

    std::unique_ptr<Builder> builder = std::make_unique<BuilderClient>();
    std::unique_ptr<Entity> entity = builder->make_entity();
    assert(entity->x == 1);
    assert(entity->y == 1);
    std::cout << "Builder pattern test passed" << '\n';
}

void test_abstract_factory() {
    std::cout << "Abstract Factory Pattern" << '\n';

    std::unique_ptr<Factory> factory = std::make_unique<FactoryClient>();
    std::unique_ptr<EntityBase> entity = factory->make_entity();
    assert(entity->get_id() == 1);
    std::cout << "Abstract factory test passed" << '\n';
}

void test_prototype_pattern() {
    std::cout << "Prototype Pattern" << '\n';

    Prototype prototype;
    std::unique_ptr<IPrototype> client = prototype.make_client();
    assert(client->get_id() == 1);
    std::cout << "Prototype pattern test passed" << '\n';
}

void test_composite_pattern() {
    std::cout << "Composite Pattern" << '\n';

    auto make_composite = [](std::size_t size_1, std::size_t size_2) {
        auto composite = std::make_unique<Composite>();
        for (std::size_t i = 0; i < size_1; ++i) {
            composite->add(std::make_unique<ClientComponent>());
        }
        for (std::size_t i = 0; i < size_2; ++i) {
            composite->add(std::make_unique<ServerComponent>());
        }
        return composite;
    };

    auto composite = std::make_unique<Composite>();
    for (std::size_t i = 0; i < 5; ++i) {
        composite->add(make_composite(1, 1));
    }

    assert(composite->test() == 15);
    std::cout << "Composite pattern test passed" << '\n';
}

void test_observer_pattern() {
    std::cout << "Observer Pattern" << '\n';

    Subject subject;
    subject.add(std::make_shared<ClientObserver>());
    subject.add(std::make_shared<ServerObserver>());

    for (int i = 0; i < 2; ++i) {
        subject.set(i + 1);
    }
    std::cout << "Observer pattern test passed" << '\n';
}

}  // namespace design_patterns

int main() {
    using namespace design_patterns;

    test_builder_pattern();
    test_abstract_factory();
    test_prototype_pattern();
    test_composite_pattern();
    test_observer_pattern();

    std::cout << "\nAll tests passed" << '\n';

    return 0;
}