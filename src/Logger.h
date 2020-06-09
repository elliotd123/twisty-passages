#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>

class Logger {
    private:
        Logger();
        std::string logFile;
        std::ofstream fileStream;
    public:

        ~Logger();

        const static int FILE = 1;
        const static int STDOUT = 2;        

        static Logger & getInstance();
        void log(const int facility, const std::string message);
};

#endif