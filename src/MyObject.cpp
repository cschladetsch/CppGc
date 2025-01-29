#include "MyObject.hpp"
#include <iostream>

MyObject::MyObject(int v) : value(v) {
    std::cout << "MyObject created: " << value << "\n";
    GC::register_object(this);
}

MyObject::~MyObject() {
    std::cout << "MyObject destroyed: " << value << "\n";
}
