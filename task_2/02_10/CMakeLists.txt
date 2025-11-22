cmake_minimum_required(VERSION 3.17)
project(quicksort LANGUAGES CXX)

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


add_library(quicksort_lib STATIC src/quicksort.cc)
add_executable(quicksort_test tests/quicksort_test.cc)
target_include_directories(quicksort_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(quicksort_test PRIVATE quicksort_lib GTest::gtest_main)