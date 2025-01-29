#include "GC.hpp"

GC& GC::instance() {
    static GC gc;
    return gc;
}

void GC::register_object(Object* obj, Generation gen) {
    spdlog::info("Registering object: {} in generation {}", fmt::ptr(obj), static_cast<int>(gen));
    instance().generations[static_cast<int>(gen)].insert(obj);
}

void Object::release_ref() {
    if (--ref_count == 0) {
        spdlog::debug("Releasing object: {}", fmt::ptr(this));
        GC::remove_object(this);
        delete this;
    }
}

void GC::remove_object(Object* obj) {
    spdlog::info("Removing object from GC: {}", fmt::ptr(obj));
    for (auto& gen : instance().generations) {
        gen.erase(obj);
    }
}

void GC::collect() {
    auto& gc = instance();
    spdlog::info("Starting garbage collection...");
    
    for (size_t i = 0; i < gc.generations.size(); ++i) {
        auto& gen = gc.generations[i];
        for (auto it = gen.begin(); it != gen.end();) {
            Object* obj = *it;
            if (obj->ref_count == 0) {
                spdlog::warn("Collecting garbage object: {}", fmt::ptr(obj));
                it = gen.erase(it);
            } else {
                ++it;
            }
        }
    }
    spdlog::info("Garbage collection complete.");
}

void GC::cleanup() {
    spdlog::info("Cleaning up all objects...");
    for (auto& gen : instance().generations) {
        for (Object* obj : gen) {
            delete obj;
        }
        gen.clear();
    }
    spdlog::info("Cleanup complete.");
}
