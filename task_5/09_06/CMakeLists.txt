cmake_minimum_required(VERSION 3.17)
project(fibonacci_iterator LANGUAGES CXX)

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

FetchContent_MakeAvailable(googletest)

add_executable(fibonacci_iterator_test fibonacci_iterator.cc fibonacci_iterator_test.cc)

target_include_directories(fibonacci_iterator_test PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(fibonacci_iterator_test PRIVATE
  GTest::gtest_main
  GTest::gmock
)

add_test(NAME run_tests COMMAND fibonacci_iterator_test)
