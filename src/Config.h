#ifndef CONFIG_H
#define CONFIG_H

#include "json.hpp"

#define DEFAULT_CONFIG_FILE "config.json"

using json = nlohmann::json;

class Config {
    static Config * instance;

    Config();
    
    public:
        static Config * getInstance();
        json data;
};

#endif