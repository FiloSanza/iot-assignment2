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

        Message& setSource(TaskId source);
        Message& setLevel(LogLevel level);
        Message& setData(String data);
        Message& setTimestamp(timestamp_t timestamp);
        Message& setDescription(String desc);
        Message& setTag(uint32_t tag);
        
        void log() const;
        TaskId getSource() const;
        String getData() const;
        LogLevel getLevel() const;
        timestamp_t getTimestamp() const;
        String getDescription() const;
        uint32_t getTag() const;

    private:
        LogLevel level;
        TaskId source;
        String data;
        String desc;
        timestamp_t timestamp;
        uint32_t tag = -1;
    };

    class Logger {
    public:
        static Logger& getInstance();
        
        Logger();
        
        void setLevel(LogLevel level);
        void log(const Message& msg);
        
        static const char* logLevelToString(LogLevel level);
    private:
        LogLevel level;
    };
}

#endif