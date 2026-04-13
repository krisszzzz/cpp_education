cmake_minimum_required(VERSION 3.17)
project(fibonacci_matrix LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED)

add_executable(fibonacci_matrix fibonacci_matrix.cc)

target_include_directories(fibonacci_matrix PRIVATE ${Boost_INCLUDE_DIRS})
