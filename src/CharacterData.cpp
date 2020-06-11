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
    }
    return c;
}

std::vector<Character> CharacterData::getCharacters() {

    std::vector<Character> characters;
    for (int i = 0; i < data.size(); i++) {
        Character c = Character();
        c.hp = data[i]["HP"].as<double>();
        c.maxHp = data[i]["HP"].as<double>();
        c.attack = data[i]["AT"].as<double>();
        c.defense = data[i]["DEF"].as<double>();
        c.description = data[i]["Description"].as<std::string>();
    }
}