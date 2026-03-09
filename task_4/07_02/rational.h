#pragma once

#include <cassert>
#include <cmath>
#include <compare>
#include <istream>
#include <numeric>
#include <ostream>
#include <type_traits>
#include <exception>

class Exception : public std::exception {
public:
    explicit Exception(const char* message) : msg(message) {}
    const char* what() const noexcept override { return msg; }
private:
    const char* msg;
};

template <typename Derived>
class Addable {
public:
    friend Derived operator+(Derived const& lhs, Derived const& rhs) {
        Derived result(lhs);
        result += rhs;
        return result;
    }
};

template <typename Derived>
class Subtractable {
public:
    friend Derived operator-(Derived const& lhs, Derived const& rhs) {
        Derived result(lhs);
        result -= rhs;
        return result;
    }
};

template <typename Derived>
class Multipliable {
public:
    friend Derived operator*(Derived const& lhs, Derived const& rhs) {
        Derived result(lhs);
        result *= rhs;
        return result;
    }
};

template <typename Derived>
class Dividable {
public:
    friend Derived operator/(Derived const& lhs, Derived const& rhs) {
        Derived result(lhs);
        result /= rhs;
        return result;
    }
};

template <typename Derived>
class Incrementable {
public:
    friend Derived& operator++(Derived& self) {
        self += Derived(1, 1);
        return self;
    }
    friend Derived operator++(Derived& self, int) {
        Derived tmp(self);
        ++self;
        return tmp;
    }
};

template <typename Derived>
class Decrementable {
public:
    friend Derived& operator--(Derived& self) {
        self -= Derived(1, 1);
        return self;
    }
    friend Derived operator--(Derived& self, int) {
        Derived tmp(self);
        --self;
        return tmp;
    }
};

template <typename T>
class Rational : public Addable<Rational<T>>,
                 public Subtractable<Rational<T>>,
                 public Multipliable<Rational<T>>,
                 public Dividable<Rational<T>>,
                 public Incrementable<Rational<T>>,
                 public Decrementable<Rational<T>> {
    static_assert(std::is_integral_v<T>, "Rational requires integral type");

public:
    Rational(T num = 0, T den = 1) : m_num(num), m_den(den) {
        if (den == 0) {
            throw Exception("denominator cannot be zero");
        }
        reduce();
    }

    explicit operator double() const { return static_cast<double>(m_num) / static_cast<double>(m_den); }

    Rational& operator+=(Rational const& other) {
        auto lcm = std::lcm(m_den, other.m_den);
        m_num = m_num * (lcm / m_den) + other.m_num * (lcm / other.m_den);
        m_den = lcm;
        reduce();
        return *this;
    }

    Rational& operator-=(Rational const& other) {
        return *this += Rational(-other.m_num, other.m_den);
    }

    Rational& operator*=(Rational const& other) {
        m_num *= other.m_num;
        m_den *= other.m_den;
        reduce();
        return *this;
    }

    Rational& operator/=(Rational const& other) {
        return *this *= Rational(other.m_den, other.m_num);
    }

    friend std::strong_ordering operator<=>(Rational const& lhs, Rational const& rhs) {
        T left = lhs.m_num * rhs.m_den;
        T right = rhs.m_num * lhs.m_den;
        if (left < right) return std::strong_ordering::less;
        if (left > right) return std::strong_ordering::greater;
        return std::strong_ordering::equal;
    }

    friend bool operator==(Rational const& lhs, Rational const& rhs) {
        return lhs.m_num == rhs.m_num && lhs.m_den == rhs.m_den;
    }

    friend std::istream& operator>>(std::istream& stream, Rational& rational) {
        return (stream >> rational.m_num).ignore() >> rational.m_den;
    }

    friend std::ostream& operator<<(std::ostream& stream, Rational const& rational) {
        return stream << rational.m_num << '/' << rational.m_den;
    }

    T numerator() const { return m_num; }
    T denominator() const { return m_den; }

private:
    void reduce() {
        if (m_den < 0) {
            m_num = -m_num;
            m_den = -m_den;
        }
        auto gcd = std::gcd(m_num, m_den);
        m_num /= gcd;
        m_den /= gcd;
    }

    T m_num;
    T m_den;
};

inline bool equal(double x, double y, double epsilon = 1e-6) {
    return std::abs(x - y) < epsilon;
}
