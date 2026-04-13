#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <numeric>
#include <utility>
#include <vector>

#include <boost/iterator/iterator_facade.hpp>

namespace fibonacci {

class Range {
public:
    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = int;
        using difference_type = std::ptrdiff_t;
        using pointer = int*;
        using reference = int;

        Iterator() : m_prev(0), m_curr(0) {}

        explicit Iterator(int prev, int curr) : m_prev(prev), m_curr(curr) {}

        reference operator*() const;
        Iterator& operator++();
        Iterator operator++(int);
        bool operator==(Iterator const& other) const;
        bool operator!=(Iterator const& other) const;

    private:
        int m_prev;
        int m_curr;
    };

    Iterator begin() const;
    Iterator end() const;
};

class BoostRange {
public:
    class Iterator : public boost::iterator_facade<Iterator, int, std::forward_iterator_tag, int> {
    public:
        Iterator() : m_prev(0), m_curr(0) {}

        explicit Iterator(int prev, int curr) : m_prev(prev), m_curr(curr) {}

    private:
        friend class boost::iterator_core_access;

        int dereference() const;
        void increment();
        bool equal(Iterator const& other) const;

        int m_prev;
        int m_curr;
    };

    Iterator begin() const;
    Iterator end() const;
};

}  // namespace fibonacci