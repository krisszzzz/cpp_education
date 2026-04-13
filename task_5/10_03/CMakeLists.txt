cmake_minimum_required(VERSION 3.17)
project(game_of_life LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED)

add_executable(game_of_life game_of_life.cc)

target_include_directories(game_of_life PRIVATE ${Boost_INCLUDE_DIRS})
