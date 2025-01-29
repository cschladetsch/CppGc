cmake_minimum_required(VERSION 3.14)
project(CppGc)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable testing
enable_testing()

# FetchContent for spdlog
include(FetchContent)
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.11.0
)
FetchContent_MakeAvailable(spdlog)

# Add main library
add_library(gc_library STATIC
    src/GC.cpp
    src/MyObject.cpp
)

# Ensure spdlog is included
target_include_directories(gc_library PRIVATE ${spdlog_SOURCE_DIR}/include)

# Add main executable
add_executable(gc_project
    src/main.cpp
)
target_link_libraries(gc_project PRIVATE gc_library spdlog::spdlog)

# Add benchmark executable
add_executable(benchmark
    src/benchmark.cpp
)
target_link_libraries(benchmark PRIVATE gc_library spdlog::spdlog)

# Add unit tests
add_executable(gc_tests tests/test_gc.cpp)
target_include_directories(gc_tests PRIVATE ${spdlog_SOURCE_DIR}/include)
target_link_libraries(gc_tests PRIVATE gc_library spdlog::spdlog)
add_test(NAME GC_Tests COMMAND gc_tests)
