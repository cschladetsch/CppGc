#define CATCH_CONFIG_MAIN
#include "../external/catch.hpp"
#include "../src/GC.hpp"
#include "../src/MyObject.hpp"

TEST_CASE("GC allocates and deallocates objects correctly") {
    auto* obj = new MyObject(10);
    obj->add_ref();
    
    REQUIRE(obj->ref_count == 1);

    obj->release_ref(); // Should trigger GC deletion
    GC::collect();
}

TEST_CASE("Multiple object handling in GC") {
    auto* obj1 = new MyObject(5);
    auto* obj2 = new MyObject(20);
    
    obj1->add_ref();
    obj2->add_ref();

    REQUIRE(obj1->ref_count == 1);
    REQUIRE(obj2->ref_count == 1);

    obj1->release_ref();
    obj2->release_ref();
    
    GC::collect();
}
