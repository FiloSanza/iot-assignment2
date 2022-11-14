#ifndef _LOGGER_H_INCLUDED
#define _LOGGER_H_INCLUDED

#include "types.h"

namespace Logger {
    enum LogLevel {
        Debug = 0,
        Info  = 1,
        Error = 2
    };

    class Message {
    public:
        Message();

        Message& setSource(String source);
        Message& setLevel(LogLevel level);
        Message& setContent(String content);
        Message& setTimestamp(timestamp_t timestamp);
        
        void log() const;
        String getSource() const;
        String getContent() const;
        LogLevel getLevel() const;
        timestamp_t getTimestamp() const;

    private:
        String source;
        String content;
        LogLevel level;
        timestamp_t timestamp;
    };

    class Logger {
    public:
        static Logger& getInstance();
        
        Logger();
        
        void setLevel(LogLevel level);
        void log(LogLevel level, const char* msg);
        void log(const Message& msg);
        
        static const char* logLevelToString(LogLevel level);
    private:

        LogLevel level;
    };
}

#endif