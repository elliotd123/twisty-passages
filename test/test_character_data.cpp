#include "doctest.h"
#include "CharacterData.h"
#include "Character.h"

CharacterData * c = c->getInstance();

TEST_CASE("Test character data") {
    SUBCASE("Test that character gets loaded") {
        Character ch = c->getCharacterByName("swordsman");
        REQUIRE(ch.classname == "Swordsman");
    }
    SUBCASE("Test nonexistent character") {
        Character ch = c->getCharacterByName("blahnonexistentblah");
        REQUIRE(ch.classname == "None");
    }
}