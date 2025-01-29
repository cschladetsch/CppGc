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
