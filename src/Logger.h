#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <queue>

class Logger {
    private:
        Logger();
        std::string logFile;
        std::ofstream fileStream;

        static Logger * instance;

        

    public:

        ~Logger();

        const static int NONE =             0;
        const static int FILE =             1;
        const static int STDOUT =   FILE << 1;
        const static int GAME =     FILE << 2;

        std::queue<std::string> messageQueue;
        std::queue<std::string> messageQueueImmediate;

        static Logger * getInstance();
        void log(const int facility, const std::string message, bool immediate=false);

        void clean();
};

#endif