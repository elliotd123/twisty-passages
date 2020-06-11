#include "CharacterData.h"

CharacterData::CharacterData() {
    data = YAML::LoadFile(CHARACTER_DATA_FILE);
}

CharacterData::~CharacterData() {
    
}

CharacterData & CharacterData::getInstance() {
    static CharacterData d;
    return d;
}

Character CharacterData::getCharacterByName(std::string name) {
    Character c = Character();
    if (data[name]) {
        c.hp = data[name]["HP"].as<double>();
        c.maxHp = data[name]["HP"].as<double>();
        c.attack = data[name]["AT"].as<double>();
        c.defense = data[name]["DEF"].as<double>();
        c.description = data[name]["Description"].as<std::string>();
        c.classname = data[name]["ClassName"].as<std::string>();
    }
    return c;
}

std::vector<Character> CharacterData::getCharacters() {

    std::vector<Character> characters;
    for (YAML::const_iterator it = data.begin(); it != data.end(); ++it) {
        Character c = Character();
        c.hp = it->second["HP"].as<double>();
        c.maxHp = it->second["HP"].as<double>();
        c.attack = it->second["AT"].as<double>();
        c.defense = it->second["DEF"].as<double>();
        c.description = it->second["Description"].as<std::string>();
        c.classname = it->second["ClassName"].as<std::string>();
        characters.push_back(c);
    }
    return characters;
}