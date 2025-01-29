# CppGc: A Simple Generational Garbage Collector in C++
**CppGc** is a lightweight **generational garbage collection system** for C++. It provides automatic memory management with reference counting and a multi-generational approach to optimize object lifespan and performance.

## **Features**
- **Base Object System**: All managed objects inherit from a base `Object` class.
- **Reference Counting**: Automatic memory management using `add_ref()` and `release_ref()`.
- **Generational Garbage Collection**:
  - Objects start in the **young** generation.
  - They move to **middle-aged** and **old** generations over time.
  - Garbage collection runs per generation for efficiency.
- **Primitive Type Support**: Manage `int`, `float`, and `std::string` with `GCPrimitive<T>`.
- **Unit Testing with Catch2**: Includes tests to verify allocation, reference management, and garbage collection.

## Usage Example
```cpp
#include "GC.hpp"
#include "MyObject.hpp"

int main() {
    {
        auto* obj1 = new MyObject(1);
        auto* obj2 = new MyObject(2);

        obj1->add_ref();
        obj2->add_ref();

        obj1->release_ref();  // Collected automatically
        obj2->release_ref();

        GC::collect(); // Run garbage collection
    }

    GC::cleanup(); // Final cleanup before exit
    return 0;
}
```

## Build & Run
```sh
mkdir build && cd build
cmake ..
make
./gc_project
```

## Run Tests
```sh
ctest --verbose
```

## License
This project is released under the **MIT License**.
