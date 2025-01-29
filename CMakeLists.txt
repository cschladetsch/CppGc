cmake_minimum_required(VERSION 3.14)
project(CppGc)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable testing
enable_testing()

# Add main executable
add_executable(gc_project
    src/main.cpp
    src/GC.cpp
    src/MyObject.cpp
)

# Add benchmark executable
add_executable(benchmark
    src/benchmark.cpp
    src/GC.cpp
    src/MyObject.cpp
)

# Include Catch2-based unit tests
add_subdirectory(tests)
