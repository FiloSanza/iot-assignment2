#include "logger.h"

#include <Arduino.h>

namespace Logger {
    Message::Message() : timestamp(millis()) {}

    Message& Message::setSource(TaskId source) {
        this->source = source;
        return *this;
    }

    Message& Message::setLevel(LogLevel level) {
        this->level = level;
        return *this;
    }

    Message& Message::setData(String data) {
        this->data = data;
        return *this;
    }

    Message& Message::setTag(uint32_t tag) {
        this->tag = tag;
        return *this;
    }

    Message& Message::setTimestamp(timestamp_t timestamp) {
        this->timestamp = timestamp;
        return *this;
    }

    Message& Message::setDescription(String desc) {
        this->desc = desc;
        return *this;
    }

    void Message::log() const {
        Logger::getInstance().log(*this);
    }

    TaskId Message::getSource() const {
        return source;
    }

    String Message::getData() const {
        return data;
    }

    uint32_t Message::getTag() const {
        return tag;
    }

    String Message::getDescription() const {
        return desc;
    }

    LogLevel Message::getLevel() const {
        return level;
    }

    timestamp_t Message::getTimestamp() const {
        return timestamp;
    }

    Logger::Logger() : level(LogLevel::Error) {
    }

    Logger& Logger::getInstance() {
        static Logger instance = Logger();
        return instance;
    }

    void Logger::setLevel(LogLevel level) {
        this->level = level;
    }

    void Logger::log(const Message& msg) {
        // Do not log if the level isn't high enough
        if (msg.getLevel() < this->level) {
            return;
        }

        String str = 
            "{\"src\": " + String(msg.getSource()) + 
            " , \"data\": " + msg.getData() + 
            ", \"desc\": " + msg.getDescription() +
            ", \"lvl\": " + String(msg.getLevel()) +
            ", \"time\": " + String(msg.getTimestamp()) +
            ", \"tag\": " + String(msg.getTag()) + " }";

        Serial.println(str);
    }

    const char* Logger::logLevelToString(LogLevel level) {
        switch (level) {
            case LogLevel::Debug: return "DEBUG";
            case LogLevel::Info:  return "INFO";
            case LogLevel::Error: return "ERROR";
            default:              return "UNKNOWN_LOG_LEVEL";
        }
    }
}