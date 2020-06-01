#define CATCH_CONFIG_MAIN

#include "catch.hpp"

TEST_CASE("Verify test framework is working", "[testing]") {
    SECTION("Testing that true is still true") {
        REQUIRE(true);
    }
}