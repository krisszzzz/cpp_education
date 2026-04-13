cmake_minimum_required(VERSION 3.17)
project(binary_tree LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(binary_tree binary_tree.cc)
