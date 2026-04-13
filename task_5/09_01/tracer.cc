#include "tracer.h"

namespace {

void helper_function() {
    trace();
    std::cout << "Helper logic executed" << '\n';
}

void outer_function() {
    trace();
    std::cout << "Outer function started" << '\n';
    helper_function();
    std::cout << "Outer function finished" << '\n';
}

}  // namespace

int main() {
    trace();

    std::cout << "Function Call" << '\n';
    outer_function();

    std::cout << "\n Local Scope" << '\n';
    {
        trace();
        std::cout << "Inside local scope" << '\n';
    }

    std::cout << "\nLoop" << '\n';
    for (auto i = 0; i < 1; ++i) {
        trace();
        std::cout << "Loop iteration" << '\n';
    }

    std::cout << "\nEnd" << '\n';

    return 0;
}