#include "Config.h"

#include <fstream>
#include <string>

Config * Config::instance = 0;

Config::Config() : YAMLExtractor(DEFAULT_CONFIG_FILE) {
    LEVEL_SIZE_X = getInt("LEVEL_SIZE_X");
    LEVEL_SIZE_Y = getInt("LEVEL_SIZE_Y");
    MAX_LEVELS = getInt("MAX_LEVELS");
    MIN_ROOMS = getInt("MIN_ROOMS");
    MAX_ROOMS = getInt("MAX_ROOMS");
    MIN_ROOM_SIZE = getInt("MIN_ROOM_SIZE");
    MAX_ROOM_SIZE = getInt("MAX_ROOM_SIZE");

    VISIBILITY_ANGLE_INCREMENT = getDouble("VISIBILITY_ANGLE_INCREMENT");
    VISIBILITY_LINEAR_INCREMENT = getDouble("VISIBILITY_LINEAR_INCREMENT");
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