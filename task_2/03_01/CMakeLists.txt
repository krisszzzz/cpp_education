cmake_minimum_required(VERSION 3.17)
project(rectangle LANGUAGES CXX)

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


add_library(rectangle_lib STATIC src/rectangle.cc)
add_executable(rectangle_test tests/rectangle_test.cc)
target_include_directories(rectangle_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(rectangle_test PRIVATE rectangle_lib GTest::gtest_main)
