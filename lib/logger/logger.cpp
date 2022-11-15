#include "logger.h"

#include <Arduino.h>
#include <ArduinoJson.h>

namespace Logger {
    Message::Message() : timestamp(millis()) {}

    Message& Message::setSource(uint32_t source) {
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

    uint32_t Message::getSource() const {
        return source;
    }

    String Message::getData() const {
        return data;
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

    Logger::Logger() : level(LogLevel::Error) {}

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

        DynamicJsonDocument json(1024);
        json["src"] = msg.getSource();
        json["data"] = msg.getData();
        json["desc"] = msg.getDescription();
        json["lvl"] = msg.getLevel();
        json["time"] = msg.getTimestamp();

        serializeJson(json, Serial);
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