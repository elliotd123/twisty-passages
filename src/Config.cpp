#include "Config.h"

#include <string>
#include <fstream>

Config * Config::instance = 0;

Config::Config() {
    std::string file = DEFAULT_CONFIG_FILE;
    std::ifstream f(file);
    f >> data;
    f.close();
}

Config * Config::getInstance() {
    if (!instance) {
        instance = new Config();
    }
    return instance;
}