#pragma once
#include <unordered_set>
#include <vector>
#include <iostream>

// Forward declaration
class GC;

class Object {
public:
    int ref_count = 0;
    virtual ~Object() = default;

    void add_ref() { ++ref_count; }
    
    void release_ref(); // Move implementation to GC.cpp
};

// Garbage Collector
class GC {
public:
    enum class Generation { YOUNG, MIDDLE, OLD };

private:
    std::vector<std::unordered_set<Object*>> generations{3};

    static GC& instance() {
        static GC gc;
        return gc;
    }

public:
    static void register_object(Object* obj, Generation gen = Generation::YOUNG);
    static void remove_object(Object* obj); // Ensure it's declared
    static void collect();
    static void cleanup();
};
