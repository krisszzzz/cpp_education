cmake_minimum_required(VERSION 3.17)
project(type_traits LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_executable(type_traits tests/type_traits_test.cc)
target_include_directories(type_traits PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

