cmake_minimum_required(VERSION 3.17)
project(stack_with_min LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(stack_with_min stack_with_min.cc)
