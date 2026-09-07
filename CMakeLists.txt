cmake_minimum_required(VERSION 3.16)

project(kvstore)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

target_include_directories(kvstore PRIVATE include)

target_include_directories(kvstore_bench PRIVATE include)