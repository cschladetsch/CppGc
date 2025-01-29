// MyObject.cpp - Updated to use GC
#include "MyObject.hpp"
#include "spdlog/spdlog.h"

MyObject::MyObject(int v) : value(v) {
    spdlog::info("MyObject created: {}", value);
    GC::register_object(this, GC::Generation::YOUNG);
}

MyObject::~MyObject() {
    spdlog::info("MyObject destroyed: {}", value);
}
