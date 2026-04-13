cmake_minimum_required(VERSION 3.17)
project(design_patterns LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(design_patterns design_patterns.cc)
