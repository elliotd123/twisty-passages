#ifndef CONFIG_H
#define CONFIG_H

#include <string>

#include "Logger.h"
#include "YAMLExtractor.h"

#define DEFAULT_CONFIG_FILE "config.yaml"

class Config : public YAMLExtractor {

    private:
        static Config * instance;

        Logger *logger = logger->getInstance();

        Config();

    public:
        static Config * getInstance();
        
        void clean();
};

#endif