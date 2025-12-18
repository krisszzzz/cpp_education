#pragma once

#include <cassert>
#include <numeric>

namespace rational {

template <int N = 0, int D = 1>
struct Ratio
{
    static_assert(D != 0, "Denominator cannot be zero");

    constexpr static auto num = N;
    constexpr static auto den = D;
};

template <typename R>
struct Reduce
{
    constexpr static auto gcd = std::gcd(R::num, R::den);
    constexpr static auto num = R::num / gcd;
    constexpr static auto den = R::den / gcd;

    using type = Ratio<num, den>;
};

template <typename R1, typename R2>
struct Sum
{
    constexpr static auto num = R1::num * R2::den + R2::num * R1::den;
    constexpr static auto den = R1::den * R2::den;

    using type = typename Reduce<Ratio<num, den>>::type;
};

template <typename R1, typename R2>
using sum = typename Sum<R1, R2>::type;

template <typename R1, typename R2>
struct Mul
{
    constexpr static auto num = R1::num * R2::num;
    constexpr static auto den = R1::den * R2::den;

    using type = typename Reduce<Ratio<num, den>>::type;
};

template <typename R1, typename R2>
using mul = typename Mul<R1, R2>::type;

template <typename R1, typename R2>
struct Div
{
    static_assert(R2::num != 0, "Division by zero in rational number");

    using type = typename Mul<R1, Ratio<R2::den, R2::num>>::type;
};

template <typename R1, typename R2>
using div = typename Div<R1, R2>::type;

template <typename R1, typename R2>
struct Sub
{
    using type = typename Sum<R1, Ratio<-R2::num, R2::den>>::type;
};

template <typename R1, typename R2>
using sub = typename Sub<R1, R2>::type;

template <typename T, typename R = Ratio<1>>
struct Duration
{
    T x = T();

    constexpr Duration() = default;
    constexpr Duration(T value) : x(value) {}
};

template <typename T1, typename R1, typename T2, typename R2>
constexpr auto operator+(const Duration<T1, R1>& lhs, const Duration<T2, R2>& rhs)
{
    constexpr auto common_den = std::lcm(R1::den, R2::den);

    auto x = lhs.x * (common_den / R1::den) * R1::num +
             rhs.x * (common_den / R2::den) * R2::num;

    return Duration<decltype(x), Ratio<1, common_den>>(x);
}

template <typename T1, typename R1, typename T2, typename R2>
constexpr auto operator-(const Duration<T1, R1>& lhs, const Duration<T2, R2>& rhs)
{
    return lhs + Duration<T2, Ratio<-R2::num, R2::den>>(rhs.x);
}

template <typename T, typename R, typename Scalar>
constexpr auto operator*(const Duration<T, R>& duration, Scalar scalar)
{
    auto x = duration.x * scalar;
    return Duration<decltype(x), R>(x);
}

template <typename Scalar, typename T, typename R>
constexpr auto operator*(Scalar scalar, const Duration<T, R>& duration)
{
    return duration * scalar;
}

template <typename T, typename R, typename Scalar>
constexpr auto operator/(const Duration<T, R>& duration, Scalar scalar)
{
    auto x = duration.x / scalar;
    return Duration<decltype(x), R>(x);
}

}