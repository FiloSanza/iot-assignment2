#include "sonar.h"

namespace Components {
    Sonar::Sonar(pin_t echo_pin, pin_t trigger_pin) 
        : echo_pin(echo_pin), trigger_pin(trigger_pin) {
        pinMode(echo_pin, INPUT);
        pinMode(trigger_pin, OUTPUT);
    }

    uint32_t Sonar::read() {
        float total = 0;

        for (int i=0; i<WATER_LEVEL_READS; i++) {
            digitalWrite(trigger_pin, LOW); 
            delayMicroseconds(3);
            digitalWrite(trigger_pin, HIGH);
            delayMicroseconds(5);
            digitalWrite(trigger_pin, LOW);

            float time_in_us = pulseIn(echo_pin, HIGH);
            float time_one_way = time_in_us * US_TO_S / 2.0;
            float distance = time_one_way * SPEED_OF_SOUND * M_TO_CM;

            total += distance;
        }

        return (uint32_t)(total / WATER_LEVEL_READS);
    }
}