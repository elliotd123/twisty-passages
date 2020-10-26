#ifndef MONSTER_DATA_H
#define MONSTER_DATA_H

#include "yaml-cpp/yaml.h"
#include "Monster.h"
#include "Logger.h"
#include "YAMLExtractor.h"

#include <string>
#include <vector>

#define MONSTER_DATA_FILE "data/monstertypes.yml"

class MonsterData : public YAMLExtractor {
    private:
        MonsterData();

        Logger *l;
        static MonsterData * instance;
        Random r;

    public:
        ~MonsterData();
        static MonsterData * getInstance();
        
        Monster getMonsterByName(std::string name);
        std::vector<Monster> monsters;
        std::vector<Monster> getMonsters();

        Monster getRandomMonster(int level);

        void clean();

};

#endif