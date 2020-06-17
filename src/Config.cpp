#include "Config.h"

#include <fstream>
#include <string>

Config * Config::instance = 0;

Config::Config() {
    std::string file = DEFAULT_CONFIG_FILE;
    data = YAML::LoadFile(file);
}

Config * Config::getInstance() {
    if (!instance) {
        instance = new Config();
    }
    return instance;
}

int Config::getInt(std::string key) {
    int result;
    if (data[key]) {
        try {
            result = data[key].as<int>();
        } catch (...) {
            result = -1;
        }
    } else {
        result = -1;
    }
    return result;
}

double Config::getDouble(std::string key) {
    double result;
    if (data[key]) {
        try {
            result = data[key].as<double>();
        } catch (...) {
            result = -1.0;
        }
    } else {
        result = -1.0;
    }
    return result;
}

std::string Config::getString(std::string key) {
    std::string result;
    if (data[key]) {
        try {
            result = data[key].as<std::string>();
        } catch (...) {
            result = "";
        }
    } else {
        result = "";
    }
    return result;
}

bool Config::getBool(std::string key) {
    bool result;
    if (data[key]) {
        try {
            result = data[key].as<bool>();
        } catch (...) {
            result = false;
        }
    } else {
        result = false;
    }
    return result;
}

void Config::clean() {
    delete(instance);
}