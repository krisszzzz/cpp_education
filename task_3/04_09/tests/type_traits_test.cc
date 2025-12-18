#include "type_traits.h"
#include <type_traits>
#include <cstdio>

// Test is_class
struct Empty {};
struct NotEmpty { int x; };
union Union { int x; };
enum Enum { A };
enum class EnumClass { A };
class Class { public: int f() { return 0; } };

static_assert(traits::is_class_v<Empty> == true, "Empty struct is a class");
static_assert(traits::is_class_v<NotEmpty> == true, "Non-empty struct is a class");
static_assert(traits::is_class_v<Class> == true, "Class is a class");
static_assert(traits::is_class_v<Union> == true, "Union is a class");
static_assert(traits::is_class_v<Enum> == false, "Enum is not a class");
static_assert(traits::is_class_v<EnumClass> == false, "Enum class is not a class");
static_assert(traits::is_class_v<int> == false, "int is not a class");
static_assert(traits::is_class_v<int*> == false, "Pointer is not a class");
static_assert(traits::is_class_v<int[]> == false, "Array is not a class");
static_assert(traits::is_class_v<int(&)[]> == false, "Reference to array is not a class");

// Test add_const
static_assert(std::is_same_v<traits::add_const_t<int>, const int>, "add_const<int> == const int");
static_assert(std::is_same_v<traits::add_const_t<const int>, const int>, "add_const<const int> == const int");
static_assert(std::is_same_v<traits::add_const_t<int*>, int* const>, "add_const<int*> == int* const");

// Test remove_const
static_assert(std::is_same_v<traits::remove_const_t<const int>, int>, "remove_const<const int> == int");
static_assert(std::is_same_v<traits::remove_const_t<int>, int>, "remove_const<int> == int");
static_assert(std::is_same_v<traits::remove_const_t<const int*>, const int*>, "remove_const<const int*> == const int*");
static_assert(std::is_same_v<traits::remove_const_t<int* const>, int*>, "remove_const<int* const> == int*");

// Test conditional
static_assert(std::is_same_v<traits::conditional_t<true, int, double>, int>, "conditional<true, int, double> == int");
static_assert(std::is_same_v<traits::conditional_t<false, int, double>, double>, "conditional<false, int, double> == double");

// Test decay
static_assert(std::is_same_v<traits::decay_t<int>, int>, "decay<int> == int");
static_assert(std::is_same_v<traits::decay_t<const int>, int>, "decay<const int> == int");
static_assert(std::is_same_v<traits::decay_t<int&>, int>, "decay<int&> == int");
static_assert(std::is_same_v<traits::decay_t<int&&>, int>, "decay<int&&> == int");
static_assert(std::is_same_v<traits::decay_t<int[]>, int*>, "decay<int[]> == int*");
static_assert(std::is_same_v<traits::decay_t<int[5]>, int*>, "decay<int[5]> == int*");
static_assert(std::is_same_v<traits::decay_t<int(int)>, int(*)(int)>, "decay<int(int)> == int(*)(int)");

int main() {
    std::printf("All compile time tests passed\n");
}