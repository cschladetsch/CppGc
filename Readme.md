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

## How CppGc is Better Than `std::shared_ptr`
`std::shared_ptr` provides **automatic reference counting**, but it lacks **true garbage collection**. **CppGc** improves upon `std::shared_ptr` in these ways:

1. **Avoids Cyclic References**  
   - `std::shared_ptr` **cannot handle cyclic references** (e.g., `A → B → A` causes a memory leak).  
   - **CppGc** allows garbage collection of objects with cycles since it periodically scans objects with `ref_count == 0` and removes them.

2. **Generational Garbage Collection**  
   - `std::shared_ptr` **immediately deletes objects when `use_count == 0`**, causing unpredictable performance spikes.  
   - **CppGc** delays deallocation using **three generations** (Young → Middle → Old), reducing fragmentation and improving performance.

3. **Explicit Garbage Collection Control**  
   - With `std::shared_ptr`, deletion happens implicitly.  
   - **CppGc** lets you control when garbage collection runs (`GC::collect()`), making it more predictable in performance-sensitive applications.

4. **Lower Overhead for Small Objects**  
   - `std::shared_ptr` requires **atomic operations** (`use_count` updates are thread-safe but slow).  
   - **CppGc** can be optimized to avoid unnecessary atomic ops by **batch-processing** garbage collection.

5. **Supports Primitive Types**  
   - `std::shared_ptr<int>` is unnecessary overhead for primitive types.  
   - **CppGc** provides a lightweight wrapper (`GCPrimitive<int>`), avoiding heap allocation overhead for simple types.

### **When to Use `std::shared_ptr` vs. CppGc**
- Use **`std::shared_ptr`** when:
  - Objects **never form cycles**.
  - You want **thread-safe reference counting**.
  - You don’t need explicit control over garbage collection.

- Use **CppGc** when:
  - Objects **form cyclic dependencies**.
  - You need **better performance with generational GC**.
  - You want **predictable, manual garbage collection control**.

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
