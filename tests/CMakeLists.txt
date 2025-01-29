add_executable(gc_tests test_gc.cpp)

# Include Catch2
target_include_directories(gc_tests PRIVATE ../external)

# Link tests with main GC source files
target_sources(gc_tests PRIVATE ../src/GC.cpp ../src/MyObject.cpp)

# Register tests with CTest
add_test(NAME GC_Tests COMMAND gc_tests)
