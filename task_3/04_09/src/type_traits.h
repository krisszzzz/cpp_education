#include <cstdint>

namespace traits {

template <typename T>
struct is_class {
private:
    template <typename U>
    static char test(int U::*);
    template <typename>
    static long test(...);
public:
    static constexpr bool value = sizeof(test<T>(0)) == sizeof(char);
};

template <typename T>
inline constexpr bool is_class_v = is_class<T>::value;


template <typename T>
struct add_const {
    using type = const T;
};

template <typename T>
struct add_const<const T> {
    using type = const T;
};

template <typename T>
using add_const_t = typename add_const<T>::type;


template <typename T>
struct remove_const {
    using type = T;
};

template <typename T>
struct remove_const<const T> {
    using type = T;
};

template <typename T>
using remove_const_t = typename remove_const<T>::type;


// conditional
template <bool B, typename T, typename F>
struct conditional {
    using type = T;
};

template <typename T, typename F>
struct conditional<false, T, F> {
    using type = F;
};

template <bool B, typename T, typename F>
using conditional_t = typename conditional<B, T, F>::type;


// Helper for decay
template <typename T>
struct remove_reference {
    using type = T;
};

template <typename T>
struct remove_reference<T&> {
    using type = T;
};

template <typename T>
struct remove_reference<T&&> {
    using type = T;
};

template <typename T>
using remove_reference_t = typename remove_reference<T>::type;

template <typename T>
struct decay {
private:
    using U = remove_reference_t<T>;
public:
    using type = conditional_t<
        is_class_v<U> ? false : (sizeof(U) != sizeof(U)),
        void,
        void
    >::type;
};

template <typename T>
struct decay<const T> {
    using type = remove_const_t<remove_reference_t<T>>;
};

template <typename T>
struct decay<T&> {
    using type = typename decay<T>::type;
};

template <typename T>
struct decay<T&&> {
    using type = typename decay<T>::type;
};

template <typename T, std::size_t N>
struct decay<T[N]> {
    using type = T*;
};

template <typename T>
struct decay<T[]> {
    using type = T*;
};

template <typename Ret, typename... Args>
struct decay<Ret(Args...)> {
    using type = Ret(*)(Args...);
};

template <typename Ret, typename... Args>
struct decay<Ret(Args..., ...)> {
    using type = Ret(*)(Args..., ...);
};

template <typename T>
using decay_t = typename decay<T>::type;

}