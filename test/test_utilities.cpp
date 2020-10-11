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
}