// GC.hpp - Updated to use spdlog for logging
#pragma once
#include <unordered_set>
#include <vector>
#include <iostream>
#include "spdlog/spdlog.h"

class Object {
public:
    int ref_count = 0;
    virtual ~Object() = default;

    void add_ref() { ++ref_count; }
    void release_ref();
};

class GC {
public:
    enum class Generation { YOUNG, MIDDLE, OLD };

private:
    std::vector<std::unordered_set<Object*>> generations{3};
    static GC& instance();

public:
    static void register_object(Object* obj, Generation gen = Generation::YOUNG);
    static void remove_object(Object* obj);
    static void collect();
    static void cleanup();
};

// MyObje
