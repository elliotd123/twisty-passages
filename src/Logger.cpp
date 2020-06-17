#include <algorithm>
#include <chrono>
#include <ctime>
#include <iostream>

#include "Logger.h"

Logger * Logger::instance = 0;

Logger::Logger() {
    logFile = "twisty.log";
    fileStream = std::ofstream(logFile);
}

Logger::~Logger() {
    fileStream.flush();
    fileStream.close();
}

Logger * Logger::getInstance() {
    if (!instance) {
        instance = new Logger();
    };
    return instance;
}

void Logger::log(const int facility, const std::string message) {

    std::chrono::system_clock::time_point time_now = std::chrono::system_clock::now();

    time_t tt;

    tt = std::chrono::system_clock::to_time_t(time_now);
    std::string timeNowString = std::string(ctime(&tt));

    timeNowString.erase(std::remove(timeNowString.begin(), timeNowString.end(), '\n'), timeNowString.end());

    std::string finalMessage = timeNowString + " - " + message;

    if (facility & FILE) {
        fileStream << finalMessage << "\n";
        fileStream.flush();
    }
    if (facility & STDOUT) {
        std::cout << finalMessage << "\n";
    }
}

void Logger::clean() {
    delete instance;
}