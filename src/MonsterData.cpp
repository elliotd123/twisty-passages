#include "MonsterData.h"
#include "Utilities.h"

#include <sstream>

MonsterData * MonsterData::instance = 0;

MonsterData::MonsterData() : YAMLExtractor(MONSTER_DATA_FILE) {
    r = Random();
    l = l->getInstance();
    l->log(Logger::FILE, "Loading monsters");
    for (const auto & keyname : YAMLData) {
        Monster m = Monster();
        m.keyname = keyname.first.as<std::string>();
        currentNode = keyname.second;
        m.hp = get<double>("HP");
        m.maxHp = get<double>("HP");
        m.attack = get<double>("AT");
        m.defense = get<double>("DEF");
        m.description = getString("Description");
        m.classname = getString("ClassName");
        m.symbol = getString("Symbol")[0];
        m.minLevel = get<int>("MinLevel");
        m.maxLevel = get<int>("MaxLevel");
        m.speed = getDouble("SPEED",1.0);
        m.visibility = getDouble("VIS",0.0);
        monsters.push_back(m);
    }
}

MonsterData::~MonsterData() {
    
}

MonsterData * MonsterData::getInstance() {
    if (!instance) {
        instance = new MonsterData();
    };
    return instance;
}

Monster MonsterData::getMonsterByName(std::string name) {
    for (Monster m : monsters) {
        if (m.keyname == name) {
            return m;
        }
    }
    Monster m = Monster();
    return m;
}

Monster MonsterData::getRandomMonster(int level) {
    int monsterLength = monsters.size();
    int counter = 0;
    while (true) {
        counter++;
        int randIdx = r.getInt(0,monsterLength-1);
        Monster m = monsters[randIdx];
        l->log(Logger::FILE,m.classname);
        if (m.minLevel <= level && m.maxLevel >= level) {
            return m;
        }
        if (counter > 100) {
            l->log(Logger::FILE,"Couldn't find a monster");
            Monster m = Monster();
            return m;
        }
    }
}

std::vector<Monster> MonsterData::getMonsters() {
    return monsters;
}

void MonsterData::clean() {
    delete(instance);
}
