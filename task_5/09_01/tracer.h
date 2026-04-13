#pragma once

#include <iostream>
#include <source_location>

namespace tracer {

class Tracer {
public:
    explicit Tracer(std::source_location loc = std::source_location::current())
        : m_loc(loc) {
        std::cout << "Entering function: " << m_loc.function_name()
                  << " (" << m_loc.file_name() << ":" << m_loc.line() << ")" << '\n';
    }

    ~Tracer() {
        std::cout << "Exiting function: " << m_loc.function_name() << '\n';
    }

    Tracer(const Tracer&) = delete;
    Tracer& operator=(const Tracer&) = delete;

private:
    std::source_location m_loc;
};

}  // namespace tracer

#ifndef NDEBUG
#define TRACE_CONCAT_IMPL(x, y) x##y
#define TRACE_CONCAT(x, y) TRACE_CONCAT_IMPL(x, y)
#define trace() tracer::Tracer TRACE_CONCAT(tracer_, __LINE__)(std::source_location::current())
#else
#define trace() ((void)0)
#endif