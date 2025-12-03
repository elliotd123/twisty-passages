#include "doctest.h"
#include "Square.h"

TEST_CASE("Test squares") {
    Square s = Square();

    SUBCASE("Floor should be walkable") {
        s.setType(FLOOR);
        REQUIRE(s.isWalkable() == true);
    }

    SUBCASE("Walls should not be walkable") {
        s.setType(WALL);
        REQUIRE(s.isWalkable() == false);
    }

    SUBCASE("Stairs should be walkable") {
        s.setType(STAIRS_UP);
        REQUIRE(s.isWalkable() == true);
        
        s.setType(STAIRS_DOWN);
        REQUIRE(s.isWalkable() == true);
    }
}