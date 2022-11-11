#include "logger.h"

#include <ArduinoSTL.h>

namespace Logger {
    Logger::Logger() : level(LogLevel::Error) {}
    
    Logger& Logger::getInstance() {
        static Logger instance = Logger();
        return instance;
    }
    
    void Logger::setLevel(LogLevel level) {
        this->level = level; 
    }
    
    void Logger::log(LogLevel level, const char* msg) {
        // Do not log if the level isn't high enough
        if (level < this->level) {
            return;
        }

        printf(
            "[%s]: %s\n", 
            Logger::logLevelToString(level),
            msg
        );
    }

    const char* Logger::logLevelToString(LogLevel level) {
        switch (level) {
            case LogLevel::Debug: return "DEBUG";
            case LogLevel::Error: return "ERROR";
            default:              return "UNKNOWN_LOG_LEVEL";
        }
    }
}