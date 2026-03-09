cmake_minimum_required(VERSION 3.10)
project(dynamic_library_loader)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

find_package(Boost 1.85 REQUIRED COMPONENTS filesystem)

message("Boost libraries: ${Boost_LIBRARIES}")

# Dynamic library version 1
add_library(library_v1 SHARED library_v1.cc)
target_include_directories(library_v1 PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(library_v1 PRIVATE ${Boost_LIBRARIES})

# Dynamic library version 2
add_library(library_v2 SHARED library_v2.cc)
target_include_directories(library_v2 PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(library_v2 PRIVATE ${Boost_LIBRARIES})

add_executable(${PROJECT_NAME} main.cc)
target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})