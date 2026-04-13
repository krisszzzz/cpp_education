cmake_minimum_required(VERSION 3.17)
project(free_list_allocator LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED)

enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG v1.8.3
)

FetchContent_MakeAvailable(googletest googlebenchmark)

add_executable(free_list_allocator_test free_list_allocator.cc)

target_include_directories(free_list_allocator_test PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(free_list_allocator_test PRIVATE
  GTest::gtest_main
  GTest::gmock
  benchmark::benchmark
)

add_test(NAME run_tests COMMAND free_list_allocator_test)
