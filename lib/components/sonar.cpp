#include "sonar.h"

namespace Components {
    Sonar::Sonar(pin_t echo_pin, pin_t trigger_pin) 
        : echo_pin(echo_pin), trigger_pin(trigger_pin) {
        pinMode(echo_pin, INPUT);
        pinMode(trigger_pin, OUTPUT);
    }

    float Sonar::read() {
        digitalWrite(trigger_pin, LOW); 
        delayMicroseconds(3);
        digitalWrite(trigger_pin, HIGH);
        delayMicroseconds(5);
        digitalWrite(trigger_pin, LOW);

        float time_in_us = pulseIn(echo_pin, HIGH);
        float time_one_way = time_in_us * US_TO_S / 2.0;
        float distance = time_one_way * SPEED_OF_SOUND * M_TO_CM;

        return  distance;
    }

    float Sonar::readAverage(uint32_t iterations) {
        float total_distance = 0.0f;
        for (uint32_t i=0; i<iterations; i++) {
            total_distance += read();
        }
        return total_distance / iterations;
    }
}