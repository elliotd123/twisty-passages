#include "Config.h"

#include <fstream>
#include <string>

Config * Config::instance = 0;

Config::Config() : YAMLExtractor(DEFAULT_CONFIG_FILE) {
   
}

Config * Config::getInstance() {
    if (!instance) {
        instance = new Config();
    }
    return instance;
}

void Config::clean() {
    delete(instance);
}