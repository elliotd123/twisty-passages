#ifndef YAML_EXTRACTOR_H
#define YAML_EXTRACTOR_H

#include <string>

#include "yaml-cpp/yaml.h"

class YAMLExtractor {

    public:
        YAML::Node YAMLData;
        YAML::Node currentNode;
        YAMLExtractor();
        YAMLExtractor(std::string file);

        void reloadYAML();

        int getInt(std::string key, int defaultVal = -1);
        double getDouble(std::string key, double defaultVal = -1.0);
        std::string getString(std::string key, std::string defaultVal = "");
        bool getBool(std::string key, bool defaultVal = false);

        template<class T> T get(std::string key, T defaultVal = (T) NULL);
    
    private:
        std::string dataString;
};

#endif