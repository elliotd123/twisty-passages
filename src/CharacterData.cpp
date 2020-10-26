#include "CharacterData.h"

#include <sstream>

CharacterData * CharacterData::instance = 0;

CharacterData::CharacterData() : YAMLExtractor(CHARACTER_DATA_FILE) {
    l = l->getInstance();
    l->log(Logger::FILE, "Loading characters");
    for (const auto & keyname : YAMLData) {
        Character c = Character();
        c.keyname = keyname.first.as<std::string>();
        currentNode = keyname.second;
        c.hp = get<double>("HP");
        c.maxHp = get<double>("HP");
        c.attack = get<double>("AT");
        c.defense = get<double>("DEF");
        c.speed = getDouble("SPEED",1.0);
        c.description = getString("Description");
        c.classname = getString("ClassName");
        c.symbol = getString("Symbol")[0];
        c.visibility = getDouble("VIS",5.0);
        characters.push_back(c);
    }
}

CharacterData::~CharacterData() {
    
}

CharacterData * CharacterData::getInstance() {
    if (!instance) {
        instance = new CharacterData();
    };
    return instance;
}

Character CharacterData::getCharacterByName(std::string name) {
    for (Character c : characters) {
        if (c.keyname == name) {
            return c;
        }
    }
    Character c = Character();
    return c;
}

std::vector<Character> CharacterData::getCharacters() {
    return characters;
}

void CharacterData::clean() {
    delete(instance);
}