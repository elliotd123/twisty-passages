#include "catch.hpp"
#include "CharacterData.h"
#include "Character.h"

CharacterData * c = c->getInstance();

TEST_CASE("Test character data", "[chardata]") {
    SECTION("Test that character gets loaded") {
        Character ch = c->getCharacterByName("swordsman");
        REQUIRE(ch.classname == "Swordsman");
    }
    SECTION("Test nonexistent character") {
        Character ch = c->getCharacterByName("blahnonexistentblah");
        REQUIRE(ch.classname == "None");
    }
}