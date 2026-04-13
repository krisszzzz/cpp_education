#pragma once

#include <cstddef>
#include <memory>
#include <vector>

namespace design_patterns {

struct Entity {
    int x = 0;
    int y = 0;
};

class Builder {
public:
    virtual ~Builder() = default;

    std::unique_ptr<Entity> make_entity();

    virtual void set_x() const = 0;
    virtual void set_y() const = 0;

protected:
    std::unique_ptr<Entity> m_entity;
};

class BuilderClient : public Builder {
public:
    void set_x() const override;
    void set_y() const override;
};

class BuilderServer : public Builder {
public:
    void set_x() const override;
    void set_y() const override;
};

class EntityBase {
public:
    virtual ~EntityBase() = default;
    virtual int get_id() const = 0;
};

class ClientEntity : public EntityBase {
public:
    int get_id() const override;
};

class ServerEntity : public EntityBase {
public:
    int get_id() const override;
};

class Factory {
public:
    virtual ~Factory() = default;
    virtual std::unique_ptr<EntityBase> make_entity() const = 0;
};

class FactoryClient : public Factory {
public:
    std::unique_ptr<EntityBase> make_entity() const override;
};

class FactoryServer : public Factory {
public:
    std::unique_ptr<EntityBase> make_entity() const override;
};

class IPrototype {
public:
    virtual ~IPrototype() = default;
    virtual std::unique_ptr<IPrototype> copy() const = 0;
    virtual int get_id() const = 0;
};

class ClientPrototype : public IPrototype {
public:
    std::unique_ptr<IPrototype> copy() const override;
    int get_id() const override;
};

class ServerPrototype : public IPrototype {
public:
    std::unique_ptr<IPrototype> copy() const override;
    int get_id() const override;
};

class Prototype {
public:
    Prototype();

    std::unique_ptr<IPrototype> make_client();
    std::unique_ptr<IPrototype> make_server();

private:
    std::vector<std::unique_ptr<IPrototype>> m_entities;
};

class Component {
public:
    virtual ~Component() = default;
    virtual int test() const = 0;
};

class ClientComponent : public Component {
public:
    int test() const override;
};

class ServerComponent : public Component {
public:
    int test() const override;
};

class Composite : public Component {
public:
    void add(std::unique_ptr<Component> component);

    int test() const override;

private:
    std::vector<std::unique_ptr<Component>> m_components;
};

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void test(int x) const = 0;
};

class Subject {
public:
    void add(std::shared_ptr<IObserver> observer);

    void set(int x);
    void notify_all() const;

private:
    int m_x = 0;
    std::vector<std::shared_ptr<IObserver>> m_observers;
};

class ClientObserver : public IObserver {
public:
    void test(int x) const override;
};

class ServerObserver : public IObserver {
public:
    void test(int x) const override;
};

void test_builder_pattern();
void test_abstract_factory();
void test_prototype_pattern();
void test_composite_pattern();
void test_observer_pattern();

}  // namespace design_patterns