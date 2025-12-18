cmake_minimum_required(VERSION 3.17)
project(fibonacci LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_executable(fibonacci tests/fibonacci_test.cc)
target_include_directories(fibonacci PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

