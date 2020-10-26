#include <cmath>

#include "catch.hpp"
#include "Utilities.h"

TEST_CASE("Test rng", "[random]") {
    Random r = Random(0);

    SECTION("Random Number Generator should reach all numbers in bounds") {
        int lower = 0;
        int higher = 1;
        bool lowerDone = false;
        bool higherDone = false;
        for (int i = 0; i < 100; i++) {
            int num = r.getInt(lower,higher);
            if (num == lower) {
                lowerDone = true;
            }
            if (num == higher) {
                higherDone = true;
            }
        }
        bool zero = (lowerDone && higherDone);

        lowerDone = false;
        higherDone = false;

        lower = 1;
        higher = 2;
        for (int i = 0; i < 100; i++) {
            int num = r.getInt(lower,higher);
            if (num == lower) {
                lowerDone = true;
            }
            if (num == higher) {
                higherDone = true;
            }
        }
        bool one = (lowerDone && higherDone);

        REQUIRE((zero && one));
    }

    SECTION("Random Number Generator should not generate numbers out of bounds") {
        int lower = 0;
        int higher = 1;
        bool inBounds = true;
        for (int i = 0; i < 100; i++) {
            int num = r.getInt(lower,higher);
            if (num > higher || num < lower) {
                inBounds = false;
            }
        }
        lower = 1;
        higher = 2;
        for (int i = 0; i < 100; i++) {
            int num = r.getInt(lower,higher);
            if (num > higher || num < lower) {
                inBounds = false;
            }
        }
        
        REQUIRE(inBounds);
    }

    SECTION("Distance calculation check 1") {
        Coord a = Coord(0,0);
        Coord b = Coord(0,0);
        double dist = distance(a,b);
        REQUIRE(dist == 0.0);
    }
    SECTION("Distance calculation check 2") {
        Coord a = Coord(0,0);
        Coord b = Coord(0,1);
        double dist = distance(a,b);
        REQUIRE(dist == 1.0);
    }
    SECTION("Distance calculation check 3") {
        Coord a = Coord(0,0);
        Coord b = Coord(1,0);
        double dist = distance(a,b);
        REQUIRE(dist == 1.0);
    }
    SECTION("Distance calculation check 4") {
        Coord a = Coord(0,0);
        Coord b = Coord(1,1);
        double dist = distance(a,b);
        REQUIRE(dist == sqrt(2.0));
    }
    SECTION("Distance calculation check 5") {
        Coord a = Coord(0,0);
        Coord b = Coord(2,2);
        double dist = distance(a,b);
        REQUIRE(dist == sqrt(8.0));
    }
}