#include "catch.hpp"

#include "Config.h"

TEST_CASE("Test Config files", "[config]") {
    Config * c = c->getInstance();
    SECTION("Test Integers are working") {
        c->data["testInt"] = 1;
        REQUIRE(c->getInt("testInt") == 1);
    }
    SECTION("Test Invalid integers return -1") {
        c->data["testInvalidInt"] = "invalidInt";
        REQUIRE(c->getInt("testInvalidInt") == -1);
    }

    SECTION("Test Doubles are working") {
        c->data["testDouble"] = 1.0;
        REQUIRE(c->getDouble("testDouble") == 1.0);
    }
    SECTION("Test invalid doubles return -1.0") {
        c->data["testInvalidDouble"] = "invalidDouble";
        REQUIRE(c->getDouble("testInvalidDouble") == -1.0);
    }

    SECTION("Test bools are working") {
        c->data["testBool"] = true;
        REQUIRE(c->getBool("testBool") == true);
    }
    SECTION("Test invalid bools return false") {
        c->data["testInvalidBool"] = "invalidBool";
        REQUIRE(!c->getBool("testInvalidBool"));
    }
}