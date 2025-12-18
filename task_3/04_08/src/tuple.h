#pragma once

#include <cstddef>
#include <utility>
#include <type_traits>

template <typename... Ts>
class Tuple {};

template <typename T, typename... Ts>
class Tuple<T, Ts...>
{
public:
    template <typename U, typename... Us>
    constexpr Tuple(U&& x, Us&&... xs)
        : m_head(std::forward<U>(x)),
          m_tail(std::forward<Us>(xs)...)
    {}

    template <std::size_t I>
    constexpr auto get() const
    {
        if constexpr (I == 0)
        {
            return m_head;
        }
        else
        {
            return m_tail.template get<I - 1>();
        }
    }

    constexpr std::size_t size() const noexcept
    {
        return sizeof...(Ts) + 1;
    }

private:
    T m_head;
    Tuple<Ts...> m_tail;
};

template <typename... Ts>
constexpr auto make_tuple(Ts&&... args)
{
    return Tuple<std::decay_t<Ts>...>(std::forward<Ts>(args)...);
}