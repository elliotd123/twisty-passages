#include "Config.h"

#include <fstream>
#include <string>

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

int Config::getInt(std::string key) {
    int result;
    try {
        result = (int) data[key];
    } catch (nlohmann::detail::type_error e) {
        //TODO: Log error
        result = -1;
    }
    return result;
}

double Config::getDouble(std::string key) {
    double result;
    try {
        result = (double) data[key];
    } catch (nlohmann::detail::type_error e) {
        //TODO: Log error
        result = -1.0;
    }
    return result;
}

std::string Config::getString(std::string key) {
    std::string result;
    try {
        result = std::string(data[key]);
    } catch (nlohmann::detail::type_error e) {
        //TODO: Log error
        result = "";
    }
    return result;
}

bool Config::getBool(std::string key) {
    bool result;
    try {
        result = (bool) data[key];
    } catch (nlohmann::detail::type_error e) {
        //TODO: Log error
        result = false;
    }
    return result;
}