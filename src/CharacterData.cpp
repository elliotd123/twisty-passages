#include "CharacterData.h"

#include <sstream>

CharacterData::CharacterData() : YAMLExtractor(CHARACTER_DATA_FILE) {
    for (const auto & keyname : YAMLData) {
        Character c = Character();
        currentNode = keyname.second;
        c.keyname = keyname.first.as<std::string>();
        c.hp = get<double>("HP");
        c.maxHp = get<double>("HP");
        c.attack = get<double>("AT");
        c.defense = get<double>("DEF");
        c.description = getString("Description");
        c.classname = getString("ClassName");
        characters.push_back(c);
    }
}

CharacterData::~CharacterData() {
    
}

CharacterData & CharacterData::getInstance() {
    static CharacterData d;
    return d;
}

Character CharacterData::getCharacterByName(std::string name) {
    Character c = Character();
    currentNode = YAML::Node(YAMLData[name]);
    c.hp = get<double>("HP");
    c.maxHp = get<double>("HP");
    c.attack = get<double>("AT");
    c.defense = get<double>("DEF");
    c.description = getString("Description");
    c.classname = getString("ClassName");
    return c;
}

std::vector<Character> CharacterData::getCharacters() {
    return characters;
}