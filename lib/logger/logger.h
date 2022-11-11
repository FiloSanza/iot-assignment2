#ifndef _LOGGER_H_INCLUDED
#define _LOGGER_H_INCLUDED

namespace Logger {
    enum LogLevel {
        Debug = 0,
        Error = 1
    };

    class Logger {
    public:
        static Logger& getInstance();
        
        Logger();
        
        void setLevel(LogLevel level);
        void log(LogLevel level, const char* msg);
    private:
        static const char* logLevelToString(LogLevel level);

        LogLevel level;
    };
}

#endif