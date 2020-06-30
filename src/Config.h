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
        int LEVEL_SIZE_X
           ,LEVEL_SIZE_Y
           ,MAX_LEVELS
           ,MIN_ROOMS
           ,MAX_ROOMS
           ,MIN_ROOM_SIZE
           ,MAX_ROOM_SIZE;

        double VISIBILITY_ANGLE_INCREMENT
              ,VISIBILITY_LINEAR_INCREMENT;
        
        void clean();
};

#endif