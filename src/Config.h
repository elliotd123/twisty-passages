#ifndef CONFIG_H
#define CONFIG_H

#include <string>

#include "json.hpp"
#include "Logger.h"

#define DEFAULT_CONFIG_FILE "config.json"

using json = nlohmann::json;

class Config {

    private:
        static Config * instance;

        Logger &logger = Logger::getInstance();

        Config();

    public:
        static Config * getInstance();
        int getInt(std::string key);
        double getDouble(std::string key);
        std::string getString(std::string key);
        bool getBool(std::string key);
        json data;
};

#endif