#include "smart_light.h"
#include "consts.h"
#include "logger.h"

namespace Tasks{
    SmartLight::SmartLight(
        Components::Led* led, 
        Components::LightSensor* light_sensor, 
        Components::Pir* pir, 
        timestamp_t period
    ) : force_off(false),
        led(led),
        light_sensor(light_sensor),
        pir(pir) {
        setPeriodAndRestartTimer(period);
    }

    void SmartLight::init() {}

    void SmartLight::tick() {
        if (!canRun()) {
            return;
        }

        markExecutedNow();

        Logger::Message msg;
        msg.setLevel(Logger::LogLevel::Debug)
           .setSource(DEFAULT_SMART_LIGHT_TASK_NAME);

        if (force_off) {
            led->turnOff();
            msg.setContent(SMART_LIGHT_FORCE_OFF_MSG)
               .log();
            return;
        }

        if (light_sensor->read() > LIGHT_SENSOR_THRESHOLD) {
            led->turnOff();
            msg.setContent(SMART_LIGHT_HIGH_AMBIENT_LIGHT)
               .log();
            return;
        }

        bool movement_detected = pir->read();
        if (movement_detected) {
            msg.setContent(SMART_LIGHT_MOVEMENT_DETECTED)
               .log();
            led->turnOn();
        } else if (millis() - pir->getLastDetectedAt() >= LIGHT_OFF_DELAY) {
            msg.setContent(SMART_LIGHT_LED_TIMEOUT)
               .log();
            led->turnOff();
        }
    }

    void SmartLight::turnOff() {
        force_off = true;
    }

    void SmartLight::turnOn() {
        force_off = false;
    }

}