#include "fibonacci_iterator.h"

namespace fibonacci {

typename Range::Iterator::reference Range::Iterator::operator*() const {
    return m_curr;
}

typename Range::Iterator& Range::Iterator::operator++() {
    int next = m_prev + m_curr;
    m_prev = m_curr;
    m_curr = next;

    return *this;
}

typename Range::Iterator Range::Iterator::operator++(int) {
    Iterator tmp = *this;
    ++(*this);
    return tmp;
}

bool Range::Iterator::operator==(Iterator const& other) const {
    return m_prev == other.m_prev && m_curr == other.m_curr;
}

bool Range::Iterator::operator!=(Iterator const& other) const {
    return !(*this == other);
}

typename Range::Iterator Range::begin() const {
    return Iterator(1, 0);
}

typename Range::Iterator Range::end() const {
    return Iterator();
}

typename BoostRange::Iterator BoostRange::begin() const {
    return Iterator(1, 0);
}

typename BoostRange::Iterator BoostRange::end() const {
    return Iterator();
}

int BoostRange::Iterator::dereference() const {
    return m_curr;
}

void BoostRange::Iterator::increment() {
    int next = m_prev + m_curr;
    m_prev = m_curr;
    m_curr = next;
}

bool BoostRange::Iterator::equal(Iterator const& other) const {
    return m_prev == other.m_prev && m_curr == other.m_curr;
}

}  // namespace fibonacci