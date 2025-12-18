cmake_minimum_required(VERSION 3.17)
project(ct_rational LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_executable(ct_rational tests/rational_test.cc)
target_include_directories(ct_rational PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
