cmake_minimum_required(VERSION 3.17)
project(quadratic_eq LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(quadratic_eq quadratic_eq.cc)
