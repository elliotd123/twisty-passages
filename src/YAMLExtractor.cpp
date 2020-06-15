#include "YAMLExtractor.h"

YAMLExtractor::YAMLExtractor() {

}

YAMLExtractor::YAMLExtractor(std::string file) {
    YAMLData = YAML::LoadFile(file);
    currentNode = YAMLData;
}

int YAMLExtractor::getInt(std::string key, int defaultVal) {
    return get<int>(key, defaultVal);
}

double YAMLExtractor::getDouble(std::string key, double defaultVal) {
    return get<double>(key, defaultVal);
}

std::string YAMLExtractor::getString(std::string key, std::string defaultVal) {
    return get<std::string>(key, defaultVal);
}

bool YAMLExtractor::getBool(std::string key, bool defaultVal) {
    return get<bool>(key, defaultVal);
}

template<class T>
T YAMLExtractor::get(std::string key, T defaultVal) {
    T result;
    if (currentNode[key]) {
        try {
            result = currentNode[key].as<T>();
        } catch (...) {
            result = defaultVal;
        }
    } else {
        result = defaultVal;
    }
    return result;
}