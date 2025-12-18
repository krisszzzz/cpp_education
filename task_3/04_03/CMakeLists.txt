cmake_minimum_required(VERSION 3.17)
project(variadic_insert LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(googletest)

add_executable(variadic_insert_test tests/variadic_insert_test.cc)
target_include_directories(variadic_insert_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(variadic_insert_test PRIVATE GTest::gtest_main)
