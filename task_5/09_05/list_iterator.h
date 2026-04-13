#pragma once

#include <iterator>
#include <memory>

namespace list_iterator {

template <typename T>
class List {
private:
    struct Node {
        T x = T();
        std::shared_ptr<Node> next;
        std::weak_ptr<Node> prev;

        Node(T value = T(), std::shared_ptr<Node> n = nullptr) : x(value), next(n) {}
    };

public:
    class Iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;

        explicit Iterator(std::shared_ptr<Node> node = nullptr) : m_node(node) {}

        Iterator operator++(int);
        Iterator& operator++();
        Iterator operator--(int);
        Iterator& operator--();

        T& operator*() const;
        T* operator->() const;

        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;

    private:
        std::shared_ptr<Node> m_node;
    };

    Iterator begin() const;
    Iterator end() const;

    void push_back(T x);

private:
    std::shared_ptr<Node> m_head;
    std::shared_ptr<Node> m_tail;
};

}  // namespace list_iterator