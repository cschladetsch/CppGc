// MyObject.hpp - Updated to inherit from Object
#pragma once
#include "GC.hpp"

class MyObject : public Object {
public:
    int value;
    MyObject(int v);
    ~MyObject();
};
