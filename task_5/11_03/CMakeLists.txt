cmake_minimum_required(VERSION 3.17)
project(quicksort_comparator LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(quicksort_comparator quicksort_comparator.cc)
