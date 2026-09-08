cmake_minimum_required(VERSION 3.16)

project(kvstore)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  DOWNLOAD_EXTRACT_TIMESTAMP true
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(kvstore
    src/main.cpp
    src/kvstore.cpp
    src/wal.cpp
)

add_executable(kvstore_bench
    benchmarks/benchmarks.cpp
    src/kvstore.cpp
    src/wal.cpp
)

enable_testing()

add_executable(kvstore_test
  tests/tests.cpp
  src/kvstore.cpp
  src/wal.cpp
)

target_link_libraries(
  kvstore_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(kvstore_test)

target_include_directories(kvstore PRIVATE include)

target_include_directories(kvstore_bench PRIVATE include)

target_include_directories(kvstore_test PRIVATE include)