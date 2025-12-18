#pragma once

template<typename Container>
void handle(Container& container, int value) {
    container.push_back(value);
}

template<typename Container, typename T>
void handle(Container& container, T value) {
    // silence warnings
    static_cast<void>(value);
    static_cast<void>(container);
}

template<typename Container, typename... Args>
void insert_pack(Container& container, Args... args) {
    (handle(container, args), ...);
}