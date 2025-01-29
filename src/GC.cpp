#include "GC.hpp"

void Object::release_ref() {
    if (--ref_count == 0) {
        GC::remove_object(this); // Now GC is fully defined
        delete this;
    }
}

void GC::remove_object(Object* obj) {
    for (auto& gen : instance().generations) {
        gen.erase(obj);
    }
}

void GC::register_object(Object* obj, Generation gen) {
    instance().generations[static_cast<int>(gen)].insert(obj);
}

void GC::collect() {
    auto& gc = instance();

    for (size_t i = 0; i < gc.generations.size(); ++i) {
        auto& gen = gc.generations[i];

        for (auto it = gen.begin(); it != gen.end();) {
            if ((*it)->ref_count == 0) {
                delete *it;
                it = gen.erase(it);
            } else {
                ++it;
            }
        }
    }

    // Promote surviving objects
    if (!gc.generations[0].empty()) {
        gc.generations[1].insert(gc.generations[0].begin(), gc.generations[0].end());
        gc.generations[0].clear();
    }
    if (!gc.generations[1].empty()) {
        gc.generations[2].insert(gc.generations[1].begin(), gc.generations[1].end());
        gc.generations[1].clear();
    }
}

void GC::cleanup() {
    auto& gc = instance();
    for (auto& gen : gc.generations) {
        for (Object* obj : gen) {
            delete obj;
        }
        gen.clear();
    }
}
