#ifndef CHARACTER_DATA_H
#define CHARACTER_DATA_H

#include "yaml-cpp/yaml.h"
#include "Character.h"
#include "Logger.h"
#include "YAMLExtractor.h"

#include <string>
#include <vector>

#define CHARACTER_DATA_FILE "data/charactertypes.yml"

class CharacterData : public YAMLExtractor {
    private:
        CharacterData();

        Logger *l;
        static CharacterData * instance;

    public:
        ~CharacterData();
        static CharacterData * getInstance();
        
        Character getCharacterByName(std::string name);
        std::vector<Character> characters;
        std::vector<Character> getCharacters();

        void clean();

};

#endif