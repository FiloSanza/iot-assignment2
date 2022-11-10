#include "sonar.h"

namespace Components {
    Sonar::Sonar(pin_t echo_pin, pin_t trigger_pin, uint32_t max_distance = MAX_SENSOR_DISTANCE) 
        : sensor(NewPing(trigger_pin, echo_pin, MAX_SENSOR_DISTANCE)) {}

    float Sonar::read() {
        return sensor.ping_cm();
    }

    float Sonar::readAverage(uint32_t iterations) {
        float total_distance = 0.0f;
        for (int i=0; i<iterations; i++) {
            total_distance += read();
        }
        return total_distance / iterations;
    }
}