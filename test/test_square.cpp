#include "catch.hpp"
#include "Square.h"

TEST_CASE("Test squares", "[squares]") {
    Square s = Square();

    SECTION("Floor should be walkable") {
        s.setType(FLOOR);
        REQUIRE(s.isWalkable() == true);
    }

    SECTION("Walls should not be walkable") {
        s.setType(WALL);
        REQUIRE(s.isWalkable() == false);
    }

    SECTION("Stairs should be walkable") {
        s.setType(STAIRS_UP);
        REQUIRE(s.isWalkable() == true);
        
        s.setType(STAIRS_DOWN);
        REQUIRE(s.isWalkable() == true);
    }
}