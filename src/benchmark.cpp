// benchmark.cpp - Updated for spdlog logging
#include <iostream>
#include <vector>
#include <memory>
#include <chrono>
#include "GC.hpp"
#include "MyObject.hpp"
#include "spdlog/spdlog.h"

class Timer {
public:
    std::chrono::high_resolution_clock::time_point start_time;
    Timer() { start_time = std::chrono::high_resolution_clock::now(); }
    double elapsed() {
        auto end_time = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double, std::milli>(end_time - start_time).count();
    }
};

double shared_ptr_test(size_t num_objects) {
    spdlog::info("Running std::shared_ptr benchmark...");
    Timer t;
    {
        std::vector<std::shared_ptr<MyObject>> objects;
        for (size_t i = 0; i < num_objects; ++i)
            objects.push_back(std::make_shared<MyObject>(i));
    }
    double time = t.elapsed();
    spdlog::info("std::shared_ptr completed in {} ms", time);
    return time;
}

double gc_test(size_t num_objects) {
    spdlog::info("Running CppGc benchmark...");
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
    double time = t.elapsed();
    spdlog::info("CppGc completed in {} ms", time);
    return time;
}

int main() {
    size_t num_objects = 100000;
    double shared_time = shared_ptr_test(num_objects);
    double gc_time = gc_test(num_objects);

    spdlog::info("\n=== Benchmark Results ===");
    spdlog::info("std::shared_ptr: {} ms", shared_time);
    spdlog::info("CppGc: {} ms", gc_time);
    spdlog::info("CppGc is {}x faster/slower", shared_time / gc_time);
    return 0;
}
