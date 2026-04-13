#include "list_iterator.h"

namespace list_iterator {

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator++(int) {
    Iterator x = *this;
    m_node = m_node->next;
    return x;
}

template <typename T>
typename List<T>::Iterator& List<T>::Iterator::operator++() {
    m_node = m_node->next;
    return *this;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator--(int) {
    Iterator x = *this;
    m_node = m_node->prev.lock();
    return x;
}

template <typename T>
typename List<T>::Iterator& List<T>::Iterator::operator--() {
    m_node = m_node->prev.lock();
    return *this;
}

template <typename T>
T& List<T>::Iterator::operator*() const {
    return m_node->x;
}

template <typename T>
T* List<T>::Iterator::operator->() const {
    return &m_node->x;
}

template <typename T>
bool List<T>::Iterator::operator==(const Iterator& other) const {
    return m_node == other.m_node;
}

template <typename T>
bool List<T>::Iterator::operator!=(const Iterator& other) const {
    return !(*this == other);
}

template <typename T>
typename List<T>::Iterator List<T>::begin() const {
    return Iterator(m_head);
}

template <typename T>
typename List<T>::Iterator List<T>::end() const {
    return Iterator();
}

template <typename T>
void List<T>::push_back(T x) {
    auto node = std::make_shared<Node>(x, nullptr);
    if (m_head) {
        m_tail->next = node;
        node->prev = m_tail;
        m_tail = node;
    } else {
        m_head = node;
        m_tail = node;
    }
}

template class List<int>;

}  // namespace list_iterator

int main() {
    list_iterator::List<int> list;
    list.push_back(1);

    for (auto iterator = std::begin(list); iterator != std::end(list); ++iterator) {
    }

    for ([[maybe_unused]] auto element : list) {
    }

    return 0;
}