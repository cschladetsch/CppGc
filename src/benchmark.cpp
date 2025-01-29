#include <iostream>
#include <vector>
#include <memory>
#include <chrono>
#include "GC.hpp"
#include "MyObject.hpp"

// Timer Utility
class Timer {
public:
    std::chrono::high_resolution_clock::time_point start_time;
    Timer() { start_time = std::chrono::high_resolution_clock::now(); }
    double elapsed() {
        auto end_time = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double, std::milli>(end_time - start_time).count();
    }
};

// Benchmark Shared Pointer
double shared_ptr_test(size_t num_objects) {
    Timer t;
    {
        std::vector<std::shared_ptr<MyObject>> objects;
        for (size_t i = 0; i < num_objects; ++i)
            objects.push_back(std::make_shared<MyObject>(i));
    }
    return t.elapsed();
}

// Benchmark CppGc
double gc_test(size_t num_objects) {
    Timer t;
    {
        std::vector<MyObject*> objects;
        for (size_t i = 0; i < num_objects; ++i) {
            auto* obj = new MyObject(i);
            obj->add_ref();
            objects.push_back(obj);
        }
        for (auto* obj : objects) obj->release_ref();
        GC::collect();
    }
    return t.elapsed();
}

int main() {
    size_t num_objects = 100000;
    double shared_time = shared_ptr_test(num_objects);
    double gc_time = gc_test(num_objects);

    std::cout << "=== Benchmark Results ===\n";
    std::cout << "std::shared_ptr: " << shared_time << " ms\n";
    std::cout << "CppGc: " << gc_time << " ms\n";
    std::cout << "CppGc is " << (shared_time / gc_time) << "x faster/slower\n";

    return 0;
}
