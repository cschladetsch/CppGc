#include "GC.hpp"
#include "MyObject.hpp"

int main() {
    {
        auto* obj1 = new MyObject(1);
        auto* obj2 = new MyObject(2);

        obj1->add_ref();
        obj2->add_ref();

        obj1->release_ref();
        obj2->release_ref();

        GC::collect();
    }

    GC::cleanup();
    return 0;
}
