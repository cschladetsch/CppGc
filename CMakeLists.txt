cmake_minimum_required(VERSION 3.14)
project(GC_Project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable testing
enable_testing()

# Create main executable
add_executable(gc_project
    src/main.cpp
    src/GC.cpp
    src/MyObject.cpp
)

# Unit tests
add_subdirectory(tests)
